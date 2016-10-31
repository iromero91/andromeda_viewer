#ifndef SHAPES_POLYLINE_H
#define SHAPES_POLYLINE_H

#include <QPointF>
#include <QList>
#include <QGraphicsItem>
#include <QPainterPath>

#include "src/drawable/drawable_primitive.h"

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
    Q_PROPERTY( QPointF startPoint READ startPoint STORED false )
    Q_PROPERTY( QPointF endPoint READ endPoint STORED false )

public:
    APolyline(QObject *parent = 0);

    //TODO this is temporarily overriden for testing
    //TODO uncomment and return to default cloner
    //virtual APolyline *clone(void) { return makeClone<APolyline>(); }
    virtual APolyline *clone(void);

    // Painter Functions
    QRectF boundingRect(void) const Q_DECL_OVERRIDE;
    QPainterPath shape(void) const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) Q_DECL_OVERRIDE;

    //TODO this class needs fixing
    LWPolypoint polypoint(int index);
    QPointF point(int index);
    double angle(int index);

    void setPoint(int index, QPointF point);
    void setAngle(int index, double angle);

    // Property getters
    bool isClosed(void) const;
    QPointF startPoint(void) const;
    QPointF endPoint(void) const;
    int pointCount(void) const { return points_.count(); }

    bool allSegmentsAreStraight(void);
    bool isSelfIntersecting(void);

    virtual void encode(AJsonObject &data) const;
    virtual void decode(AJsonObject &data, bool undoable = true);

public slots:
    void clear() { points_.clear(); }
    bool addPoint(LWPolypoint point);
    bool addPoint(QPointF point, double angle=0);
    void close(void);
    void normalize(void);

protected:
    // Properties unique to the polyline class
    QList<LWPolypoint> points_;
};

#endif // SHAPES_POLYLINE_H
