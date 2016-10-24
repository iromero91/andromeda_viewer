#include "polyline_tool_base.h"

PolylineDrawingToolBase::PolylineDrawingToolBase() :
    ADrawingTool()
{
}

void PolylineDrawingToolBase::reset()
{
    points_.clear();

    setToolState((int) LINE_TOOL_STATE::FIRST_POINT);
}

void PolylineDrawingToolBase::start()
{
    reset();

    setVisible(true);
}

void PolylineDrawingToolBase::start(QPointF pos)
{
    start();

    start_pos_ = pos;

    setToolState((int) LINE_TOOL_STATE::ADDING_POINTS);
}

void PolylineDrawingToolBase::addPoint(QPointF point)
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

void PolylineDrawingToolBase::finish()
{

}
