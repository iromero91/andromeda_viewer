#include "polyline_tool.h"

PolylineDrawingTool::PolylineDrawingTool() :
    AToolBase()
{
}

QRectF PolylineDrawingTool::boundingRect() const
{
    QRectF rect(start_pos_, QSizeF(0,0));

    foreach (QPointF point, points_)
    {
        rect = rect.united(QRectF(point, QSizeF(0,0)));
    }

    // include the tool position
    rect = rect.united(QRectF(tool_pos_, QSizeF(0,0)));

    //rect.adjust(-t, -t, t, t);

    return rect;
}

QPainterPath PolylineDrawingTool::shape() const
{
    QPainterPath path;

    path.moveTo(start_pos_);

    foreach (QPointF p, points_)
    {
        path.lineTo(p);
    }

    return path;
}

void PolylineDrawingTool::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setBrush(Qt::NoBrush);

    QPen p;
    p.setColor(DRAWING_TOOL_OUTLINE_COLOR);
    painter->setPen(p);

    if (points_.count() > 0)
    {
        painter->drawPath(shape());
    }

    if (getToolState() > (int) LINE_TOOL_STATE::FIRST_POINT)
    {
        QPointF last = points_.count() == 0 ? start_pos_ : points_.last();

        p.setColor(DRAWING_TOOL_TRACE_LINE_COLOR);
        p.setStyle(Qt::DashLine);

        painter->setPen(p);

        painter->drawLine(last, tool_pos_);
    }
}

void PolylineDrawingTool::reset()
{
    points_.clear();

    setToolState((int) LINE_TOOL_STATE::FIRST_POINT);
}

void PolylineDrawingTool::start()
{
    reset();

    setVisible(true);
}

void PolylineDrawingTool::start(QPointF pos)
{
    start();

    start_pos_ = pos;

    setToolState((int) LINE_TOOL_STATE::ADDING_POINTS);
}

void PolylineDrawingTool::addPoint(QPointF point)
{
    if (getToolState() == (int) LINE_TOOL_STATE::FIRST_POINT)
    {
        start_pos_ = point;
        setToolState((int) LINE_TOOL_STATE::ADDING_POINTS);
    }
    else
    {
        points_.append(point);
    }
}

APolyline PolylineDrawingTool::getPolyline()
{
    APolyline line;

    line.addPoint(start_pos_);

    foreach (QPointF p, points_)
    {
        line.addPoint(p);
    }
}

void PolylineDrawingTool::finish()
{

}
