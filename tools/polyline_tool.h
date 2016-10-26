#ifndef POLYLINE_TOOL_H
#define POLYLINE_TOOL_H

#include "polyline_drawing_tool_base.h"
#include "shapes/polyline.h"

class PolylineDrawingTool : public PolylineDrawingToolBase
{
    Q_OBJECT

public:
    PolylineDrawingTool(QObject *parent = 0);
};

#endif // POLYLINE_TOOL_H

