#include "andromeda_ellipse.h"

#include <math.h>

AndromedaEllipse::AndromedaEllipse() :
     AndromedaDrawable(),
     rx_(0),
     ry_(0)
{
}

QRectF AndromedaEllipse::boundingRect() const
{
    QRectF rect(-rx_, -ry_, 2*rx_, 2*ry_);

    rect.adjust(-thickness_,
                -thickness_,
                 thickness_,
                 thickness_);

    return rect;
}

QPainterPath AndromedaEllipse::shape() const
{
    QPainterPath path;

    path.addEllipse(QPointF(0,0), rx_, ry_);

    return path;
}

void AndromedaEllipse::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    //QPainterPath path = shape();

    QPen pen = linePen_;
    QBrush brush = fillBrush_;

    QColor c = linePen_.color();

    if (isSelected())
        c = c.dark();

    c = (option->state & QStyle::State_MouseOver) ? c.light() : c;

    pen.setColor(c);

    painter->setPen(pen);

    /*
    if (filled_)
    {
        c = brush.color();

        if (isSelected())
            c = c.dark();

        brush.setColor(c);

        painter->setBrush(brush);
    }
    else
    {
        painter->setBrush(Qt::NoBrush);
    }
    */
    painter->setBrush(QBrush(SYMBOL_FILL_COLOR));

    painter->drawEllipse(QPointF(0,0), rx_, ry_);

    if (drawBoundingBox_)
        drawBoundingBox(painter);

}

void AndromedaEllipse::setRadius(double rx, double ry)
{
    rx_ = fabs(rx);
    ry_ = fabs(ry);

    prepareGeometryChange();

    update();
}

void AndromedaEllipse::setRadius(double r)
{
    setRadius(r,r);
}
