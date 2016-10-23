#include "andromeda_rect.h"

AndromedaRect::AndromedaRect() :
    AndromedaDrawable(),
    w_(0),
    h_(0)
{

}

QRectF AndromedaRect::getRect() const
{
    return QRectF(QPointF(0,0), QSizeF(w_, h_));
}

QRectF AndromedaRect::boundingRect() const
{
    QRectF rect = getRect();

    rect.adjust(-thickness_,
                -thickness_,
                 thickness_,
                 thickness_);

    return rect;
}

QPainterPath AndromedaRect::shape() const
{
    QPainterPath path;

    path.addRect(getRect());

    return path;
}

void AndromedaRect::setSize(double width, double height)
{
    w_ = width;
    h_ = height;

    prepareGeometryChange();

    update();
}

void AndromedaRect::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QPen pen = linePen_;
    QBrush brush = fillBrush_;

    QColor c = linePen_.color();

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
