#ifndef SHAPES_ELLIPSE_H
#define SHAPES_ELLIPSE_H

#include "shapes/drawable.h"

#include <QPainterPath>

class AEllipse : public ADrawable
{

public:
    AEllipse();

    QRectF boundingRect() const Q_DECL_OVERRIDE;
    QPainterPath shape() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

    void setRadius(double r);
    void setRadius(double rx, double ry);

    double getRx(void) { return rx_; }
    double getRy(void) { return ry_; }

protected:
    // Radii
    double rx_;
    double ry_;
};

#endif // SHAPES_ELLIPSE_H

