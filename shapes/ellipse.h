#ifndef SHAPES_ELLIPSE_H
#define SHAPES_ELLIPSE_H

#include "shapes/drawable.h"
#include "geometry/geometry.h"

#include <QPainterPath>

class AEllipse : public ADrawable
{

public:
    AEllipse();
    virtual AEllipse *clone() { return makeClone<AEllipse>(); }

    QRectF boundingRect() const Q_DECL_OVERRIDE;
    QPainterPath shape() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

    void setRadius(double r);
    void setRadius(double rx, double ry);

    double getRx(void) { return rx_; }
    double getRy(void) { return ry_; }

    bool isCircle(double threshold = AGeometry::DISTANCE_EPSILON) { return fabs(rx_ - ry_) < threshold; }

protected:
    // Radii
    double rx_ = 0;
    double ry_ = 0;
};

#endif // SHAPES_ELLIPSE_H

