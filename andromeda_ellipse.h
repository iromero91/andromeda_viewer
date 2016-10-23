#ifndef ANDROMEDA_ELLIPSE_H
#define ANDROMEDA_ELLIPSE_H

#include "andromeda_drawable.h"

#include <QPainterPath>

class AndromedaEllipse : public AndromedaDrawable
{
public:
    AndromedaEllipse();

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

#endif // ANDROMEDA_ELLIPSE_H

