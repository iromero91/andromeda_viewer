#ifndef LWPOLYLINE_H
#define LWPOLYLINE_H

#include <QPointF>
#include <QList>

#include <QGraphicsItem>
#include <QPainterPath>

#include "andromeda_drawable.h"

const double PT_EPSILON = 0.01;

typedef struct

{
    QPointF point;
    double angle;
} LWPolypoint;

class LWPolyline : public AndromedaDrawable
{
public:
    LWPolyline();

    QRectF boundingRect() const Q_DECL_OVERRIDE;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) Q_DECL_OVERRIDE;

    QPainterPath shape() const;

    void clear() { points_.clear(); }

    bool isClosed();

    bool addPoint(LWPolypoint point);
    bool addPoint(QPointF point, double angle=0);

    static bool comparePoints(QPointF pA, QPointF pB, double epsilon = PT_EPSILON);

    QList<LWPolypoint> points_;
};

#endif // LWPOLYLINE_H
