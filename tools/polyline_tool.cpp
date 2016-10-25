#include "polyline_tool.h"
#include "geometry/geometry.h"

#include <QDebug>

PolylineDrawingTool::PolylineDrawingTool(QObject *parent) : AToolBase(parent)
{

}

void PolylineDrawingTool::onReset()
{
    points_.clear();
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

    if (points_.count() > 0)
    {
        QPainterPath path(start_pos_);

        foreach (QPointF point, points_)
        {
            path.lineTo(point);
        }

        if (path.intersects(rect))
        {
            painter->drawPath(path);
        }
    }

    if (getToolState() > TOOL_STATE::POLYLINE_SET_ORIGIN)
    {
        QPointF last = points_.count() == 0 ? start_pos_ : points_.last();

        p.setColor(DRAWING_TOOL_TRACE_LINE_COLOR);
        p.setStyle(Qt::DashLine);

        painter->setPen(p);

        painter->drawLine(last, tool_pos_);
    }
}

bool PolylineDrawingTool::addPoint(QPointF point)
{
    switch (getToolState())
    {
    default:
    case TOOL_STATE::POLYLINE_SET_ORIGIN:
        // Set the starting position
        reset();
        setToolState(TOOL_STATE::POLYLINE_ADD_POINT);

        setStartPos(point);
        break;
    case TOOL_STATE::POLYLINE_ADD_POINT:
        if (points_.count() > 1)
        {
            if (AGeometry::PointsAreCoincident(point, start_pos_))
            {
                // Close the polygon and finish
                points_.append(start_pos_);
                finish();
                return true;
            }
        }
        points_.append(point);
    }

    // False indicates that the polygon did not close itself
    return false;
}

void PolylineDrawingTool::getPolyline(APolyline &line)
{
    line.clear();

    line.setStartPos(start_pos_);

    foreach (QPointF p, points_)
    {
        line.addPoint(p);
    }

    line.setFilled(true);
}

bool PolylineDrawingTool::onMousePress(QMouseEvent *event, QPointF cursorPos)
{
    bool handled = false;

    switch (event->button())
    {
    case Qt::LeftButton:
        addPoint(cursorPos);
        handled = true;
        break;
    default:
        break;
    }

    return handled;
}

bool PolylineDrawingTool::onMouseDoubleClick(QMouseEvent *event, QPointF cursorPos)
{
    bool handled = false;

    switch (event->button())
    {
    case Qt::LeftButton:
        // If the polyline didn't finish by itself, enforce closing
        if (!addPoint(cursorPos))
        {
            finish();
        }
        handled = true;
        break;

    default:
        break;
    }

    return handled;
}
