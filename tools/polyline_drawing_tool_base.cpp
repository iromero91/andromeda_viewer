#include "polyline_drawing_tool_base.h"
#include "geometry/geometry.h"

PolylineDrawingToolBase::PolylineDrawingToolBase(QObject *parent) : AToolBase(parent)
{

}

void PolylineDrawingToolBase::paintHints(QPainter *painter, const QRectF &rect)
{
    Q_UNUSED(rect);

    if (painter == nullptr)
        return;

    painter->setPen(hints_pen_);

    switch (getToolState())
    {
    case TOOL_STATE::POLYLINE_ADD_POINT:
        painter->setPen(hints_pen_);
        painter->drawLine(tool_pos_, start_pos_);
        break;
    default:
        break;
    }
}

void PolylineDrawingToolBase::paintTool(QPainter *painter, const QRectF &rect)
{
    if (painter == nullptr)
        return;

    painter->setBrush(tool_brush_);

    if (points_.count() > 0)
    {
        painter->setPen(tool_pen_);
        QPainterPath path(start_pos_);

        foreach (QPointF point, points_)
        {
            path.lineTo(point);
        }

        path.lineTo(tool_pos_);

        if (path.intersects(rect))
        {
            painter->drawPath(path);
        }
    }
}

bool PolylineDrawingToolBase::addPoint(QPointF point)
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
                return true;
            }
        }
        points_.append(point);
    }

    // False indicates that the polygon did not close itself
    return false;
}

bool PolylineDrawingToolBase::onMousePress(QMouseEvent *event, QPointF cursorPos)
{
    if (event->button() == Qt::LeftButton)
    {
        if (addPoint(cursorPos))
        {
            finish();
        }

        return true;
    }

    return false;
}

bool PolylineDrawingToolBase::onMouseDoubleClick(QMouseEvent *event, QPointF cursorPos)
{
    if (event->button() == Qt::LeftButton)
    {
        if (event->modifiers() & Qt::ShiftModifier)
        {
            addPoint(start_pos_);
        }
        else
        {
            addPoint(cursorPos);
        }

        finish();

        return true;
    }

    return false;
}

void PolylineDrawingToolBase::getPolyline(APolyline &line)
{
    line.clear();

    line.setStartPos(start_pos_);

    foreach (QPointF p, points_)
    {
        line.addPoint(p);
    }

    line.setFilled(true);
}

void PolylineDrawingToolBase::onReset()
{
    points_.clear();
}
