#ifndef SHAPES_ELLIPSE_H
#define SHAPES_ELLIPSE_H

#include <QPainterPath>

#include "src/geometry/geometry.h"
#include "src/drawable/drawable_primitive.h"

class AEllipse : public ADrawablePrimitive
{
    Q_OBJECT

    Q_PROPERTY( double rx READ rx WRITE setRx )
    Q_PROPERTY( double ry READ ry WRITE setRy )
    Q_PROPERTY( bool circular READ isCircular STORED false )

public:
    AEllipse(QObject *parent = 0);
    virtual AEllipse *clone() { return makeClone<AEllipse>(); }

    // Painter Functions
    QRectF boundingRect() const Q_DECL_OVERRIDE;
    QPainterPath shape() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

    // Property getters
    QPointF radius(void) const { return QPointF(rx_, ry_); }
    double rx(void) const { return rx_; }
    double ry(void) const { return ry_; }

    bool isCircular(double threshold = AGeometry::DISTANCE_EPSILON) const { return fabs(rx_ - ry_) < threshold; }

    virtual void encode(QJsonObject &json) const;
    virtual void decode(QJsonObject &json, bool undoable = true);

public slots:
    void setRadius(double rx, double ry);
    void setRadius(double r) { setRadius(r,r); }
    void setRadius(QPointF radius) { setRadius(radius.x(), radius.y()); }
    void setRx(double rx) { setRadius(rx, ry_); }
    void setRy(double ry) { setRadius(rx_, ry); }

protected:
    // Properties unique to the ellipse class
    double rx_ = 0;
    double ry_ = 0;
};

#endif // SHAPES_ELLIPSE_H

