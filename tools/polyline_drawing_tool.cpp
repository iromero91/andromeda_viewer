#include "polyline_drawing_tool.h"
#include "geometry/geometry.h"

PolylineDrawingTool::PolylineDrawingTool(QObject *parent) : PolylineToolBase(parent)
{

}

void PolylineDrawingTool::finalAction()
{
    if (QApplication::keyboardModifiers() & Qt::ShiftModifier)
    {
        addPoint(start_pos_);
    }
    else
    {
        addPoint(tool_pos_);
    }

    finish();
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

        start_pos_ = point;
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

        if (points_.count() > 0)
        {
            if (AGeometry::PointsAreCoincident(point, points_.last()))
            {
                return false;
            }
        }
        else
        {
            if (AGeometry::PointsAreCoincident(point, start_pos_))
            {
                return false;
            }
        }

        points_.append(point);
        break;
    }

    // False indicates that the polygon did not close itself
    return false;
}
