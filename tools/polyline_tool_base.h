#ifndef POLYLINE_TOOL_BASE_H
#define POLYLINE_TOOL_BASE_H

#include "drawing_tool_base.h"
#include "shapes/polyline.h"

enum class LINE_TOOL_STATE : int {
    FIRST_POINT = 0,    // Adding the first point
    ADDING_POINTS,      // Adding subsequent points
};

class PolylineDrawingToolBase : public ADrawingTool
{
    Q_OBJECT

public:
    PolylineDrawingToolBase();

    // Return the polyline constructed by this tool
    APolyline getPolyline(void);

public slots:
    void reset(void);
    void start(void);
    void start(QPointF pos);
    void addPoint(QPointF point);
    void finish();

protected:

    QPointF start_pos_;

    QList<QPointF> points_;

};

#endif // POLYLINE_TOOL_BASE_H

