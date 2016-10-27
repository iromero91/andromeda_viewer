#ifndef POLYLINE_EDITING_TOOL_H
#define POLYLINE_EDITING_TOOL_H

#include "tool_base.h"
#include "shapes/polyline.h"

class PolylineEditingTool : public AToolBase
{
    Q_OBJECT

public:
    PolylineEditingTool(QObject *parent = 0);
};

#endif // POLYLINE_EDITING_TOOL_H

