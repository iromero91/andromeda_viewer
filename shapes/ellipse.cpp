#include "ellipse.h"

#include <math.h>

AEllipse::AEllipse(QObject *parent) : ADrawablePrimitive(parent)
{
    setObjectName("AEllipse");
}

void AEllipse::decode(QJsonObject &json)
{
    ADrawablePrimitive::decode(json);
}

void AEllipse::encode(QJsonObject &json) const
{
    ADrawablePrimitive::encode(json);

    if (isCircular())
    {
        json[JSON_KEY::RADIUS] = rx();
    }
    else
    {
        json[JSON_KEY::RADIUS_X] = rx();
        json[JSON_KEY::RADIUS_Y] = ry();
    }

    json[JSON_KEY::POS_X] = pos().x();
    json[JSON_KEY::POS_Y] = pos().y();
}

QRectF AEllipse::boundingRect() const
{
    QRectF rect(-rx_, -ry_, 2*rx_, 2*ry_);

    double offset = line_width_ / 2;

    rect.adjust(-offset,
                -offset,
                 offset,
                 offset);

    return rect;
}

QPainterPath AEllipse::shape() const
{
    QPainterPath path;

    path.addEllipse(QPointF(0,0), rx_, ry_);

    return path;
}

void AEllipse::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(widget);

    painter->setPen(pen(option));
    painter->setBrush(brush(option));

    painter->drawEllipse(QPointF(0,0), rx_, ry_);

    if (draw_bounding_box_)
        drawBoundingBox(painter);

}

void AEllipse::setRadius(double rx, double ry)
{
    if (rx != 0)
        rx_ = fabs(rx);

    if (ry != 0)
        ry_ = fabs(ry);

    prepareGeometryChange();

    update();
}
