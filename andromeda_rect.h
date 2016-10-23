
#ifndef ANDROMEDA_RECT_H
#define ANDROMEDA_RECT_H

#include "andromeda_drawable.h"
#include <QPainterPath>

class AndromedaRect : public AndromedaDrawable
{
public:
    AndromedaRect();

    QRectF boundingRect() const Q_DECL_OVERRIDE;
    QPainterPath shape() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

    QRectF getRect(void) const;

    void setSize(double width, double height);
    void setWidth(double width) { setSize(width, h_); }
    void setHeight(double height) { setSize(w_, height); }

protected:
    double w_;  // width
    double h_;  // height
};

#endif // ANDROMEDA_RECT_H

