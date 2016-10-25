#ifndef POLYLINE_TOOL_H
#define POLYLINE_TOOL_H

#include "tool_base.h"
#include "shapes/polyline.h"

enum class LINE_TOOL_STATE : int {

    FIRST_POINT = 10,    // Adding the first point
    ADDING_POINTS,      // Adding subsequent points
};

class PolylineDrawingTool : public AToolBase
{
    Q_OBJECT

public:
    PolylineDrawingTool();

    // Return the polyline constructed by this tool
    void getPolyline(APolyline &line);

    void paint(QPainter *painter, const QRectF &rect);

public slots:
    void reset(void);
    void start(void);
    void addPoint(QPointF point);
    void finish();

    void onMousePress(QMouseEvent *event);

protected:

    QPointF start_pos_;

    QList<QPointF> points_;

};

#endif // POLYLINE_TOOL_H

