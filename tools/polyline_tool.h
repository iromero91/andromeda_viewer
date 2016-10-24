#ifndef POLYLINE_TOOL_H
#define POLYLINE_TOOL_H

#include "tool_base.h"
#include "shapes/polyline.h"

enum class LINE_TOOL_STATE : int {
    FIRST_POINT = 0,    // Adding the first point
    ADDING_POINTS,      // Adding subsequent points
};

class PolylineDrawingTool : public AToolBase
{
    Q_OBJECT

public:
    PolylineDrawingTool();

    // Return the polyline constructed by this tool
    APolyline getPolyline(void);

    // Painting functions
    QRectF boundingRect() const;
    QPainterPath shape() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

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

#endif // POLYLINE_TOOL_H

