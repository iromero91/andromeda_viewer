#ifndef SHAPES_POLYLINE_H
#define SHAPES_POLYLINE_H

#include <QPointF>
#include <QList>

#include <QGraphicsItem>
#include <QPainterPath>

#include "drawable_primitive.h"

//TODO fix this, is hacky
typedef struct
{
    QPointF point;
    double angle;
} LWPolypoint;

class APolyline : public ADrawablePrimitive
{
    Q_OBJECT

    Q_PROPERTY( bool closed READ isClosed STORED false )
    Q_PROPERTY( int pointCount READ pointCount STORED false )
    Q_PROPERTY( QPointF startPoint READ startPoint )
    Q_PROPERTY( QPointF endPoint READ endPoint )

public:
    APolyline(QObject *parent = 0);
    virtual APolyline *clone(void) { return makeClone<APolyline>(); }

    // Painter Functions
    QRectF boundingRect() const Q_DECL_OVERRIDE;
    QPainterPath shape() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) Q_DECL_OVERRIDE;

    //TODO this class needs fixing
    void setStartPos(QPointF pos) { start_pos_ = pos; }
    QPointF getStartPos(void) { return start_pos_; }

    LWPolypoint getPolypoint(int index);
    QPointF getPoint(int index);
    double getAngle(int index);

    void setPoint(int index, QPointF point);
    void setAngle(int index, double angle);

    // Property getters
    bool isClosed();
    QPointF startPoint(void) { return start_pos_; }
    QPointF endPoint(void);
    int pointCount(void) { return points_.count() + 1; }


public slots:
    void clear() { points_.clear(); }
    bool addPoint(LWPolypoint point);
    bool addPoint(QPointF point, double angle=0);


protected:
    // Properties unique to the polyline class
    QPointF start_pos_;
    QList<LWPolypoint> points_;
};

#endif // SHAPES_POLYLINE_H
