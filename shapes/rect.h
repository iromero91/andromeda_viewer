#ifndef SHAPES_RECT_H
#define SHAPES_RECT_H

#include "shapes/drawable.h"
#include <QPainterPath>

class ARect : public ADrawable
{

public:
    ARect();

    virtual ARect *clone(void) { return makeClone<ARect>(); }

    QRectF boundingRect() const Q_DECL_OVERRIDE;
    QPainterPath shape() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

    QRectF getRect(void) const;

    void setSize(double width, double height);
    void setWidth(double width) { setSize(width, h_); }
    void setHeight(double height) { setSize(w_, height); }

protected:
    double w_ = 0;  // width
    double h_ = 0;  // height
};

#endif // SHAPES_RECT_H

