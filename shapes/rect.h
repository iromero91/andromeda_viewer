#ifndef SHAPES_RECT_H
#define SHAPES_RECT_H

#include "shapes/drawable.h"
#include <QPainterPath>

class ARect : public ADrawable
{
    Q_OBJECT

public:
    ARect();

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

#endif // SHAPES_RECT_H

