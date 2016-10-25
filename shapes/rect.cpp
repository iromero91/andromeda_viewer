#include "rect.h"

ARect::ARect() : ADrawable()
{

}

QRectF ARect::getRect() const
{
    return QRectF(QPointF(0,0), QSizeF(w_, h_));
}

QRectF ARect::boundingRect() const
{
    QRectF rect = getRect();

    rect.adjust(-thickness_,
                -thickness_,
                 thickness_,
                 thickness_);

    return rect;
}

QPainterPath ARect::shape() const
{
    QPainterPath path;

    path.addRect(getRect());

    return path;
}

void ARect::setSize(double width, double height)
{
    w_ = width;
    h_ = height;

    prepareGeometryChange();

    update();
}

void ARect::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(widget);

    QPen pen = line_pen_;
    QBrush brush = fill_brush_;

    QColor c = line_pen_.color();

    if (isSelected())
        c = c.dark();

    c = (option->state & QStyle::State_MouseOver) ? c.light() : c;

    pen.setColor(c);

    painter->setPen(pen);

    painter->setBrush(Qt::NoBrush);

    painter->drawRect(getRect());

    if (drawBoundingBox_)
        drawBoundingBox(painter);
}
