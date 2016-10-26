#include "rect_drawing_tool.h"

RectDrawingTool::RectDrawingTool(QObject *parent) : PolylineDrawingToolBase(parent)
{

}

bool RectDrawingTool::addPoint(QPointF point)
{
    QRectF rect(start_pos_, point);

    switch (getToolState())
    {
    default:
    case TOOL_STATE::POLYLINE_SET_ORIGIN:
        reset();
        start_pos_ = point;
        setToolState(TOOL_STATE::POLYLINE_ADD_POINT);
        break;
    case TOOL_STATE::POLYLINE_ADD_POINT:
        points_.clear();

        if (rect.width() == 0 || rect.height() == 0)
        {
            return false;
        }

        points_.append(rect.topRight());
        points_.append(rect.bottomRight());
        points_.append(rect.bottomLeft());
        points_.append(rect.topLeft());

        // Return true to signify finished
        return true;
    }

    return false;
}

void RectDrawingTool::paintTool(QPainter *painter, const QRectF &rect)
{
    Q_UNUSED(rect);

    if (painter == nullptr)
        return;

    if (getToolState() > TOOL_STATE::POLYLINE_SET_ORIGIN)
    {
        painter->setPen(tool_pen_);
        painter->setBrush(tool_brush_);

        painter->drawRect(QRectF(start_pos_, tool_pos_));
    }
}

void RectDrawingTool::paintHints(QPainter *painter, const QRectF &rect)
{
    Q_UNUSED(rect);

    if (painter == nullptr)
        return;

    if (getToolState() > TOOL_STATE::POLYLINE_SET_ORIGIN)
    {
        painter->setPen(hints_pen_);

        painter->drawLine(start_pos_, tool_pos_);
    }
}
