#include "polyline_tool.h"

#include <QDebug>

PolylineDrawingTool::PolylineDrawingTool() : AToolBase()
{
}

void PolylineDrawingTool::paint(QPainter *painter, const QRectF &rect)
{
    painter->setBrush(Qt::NoBrush);

    //TODO allow tool pen to be changed
    QPen p;
    p.setColor(DRAWING_TOOL_OUTLINE_COLOR);
    p.setWidthF(1.5);
    p.setCosmetic(true);
    p.setStyle(Qt::SolidLine);
    painter->setPen(p);

    QPainterPath path(start_pos_);

    foreach (QPointF point, points_)
    {
        path.lineTo(point);
    }

    if (path.intersects(rect))
    {
        painter->drawPath(path);
    }

    // Draw a line from most-recent point to the current cursor position
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

void PolylineDrawingTool::getPolyline(APolyline &line)
{
    line.clear();

    line.addPoint(start_pos_);

    foreach (QPointF p, points_)
    {
        line.addPoint(p);
    }
}

void PolylineDrawingTool::finish()
{

}

void PolylineDrawingTool::onMousePress(QMouseEvent *event)
{
    switch (event->button())
    {
    case Qt::LeftButton:

    }
}
