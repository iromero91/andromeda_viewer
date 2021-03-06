#include <QPen>
#include <QPainter>
#include <QStyleOptionGraphicsItem>
#include <QDebug>
#include <QGraphicsObject>

#include "drawable_base.h"

ADrawableBase::ADrawableBase(QObject *parent) :
    AndromedaObject(parent),
    QGraphicsItem()
{
    setObjectName(OBJECT_NAME::A_DRAWABLE_BASE);

    // Bounding Box Pen
    bounding_box_pen_.setColor(SYMBOL_BB_COLOR);
    bounding_box_pen_.setWidthF(2.5);
    //bounding_box_pen_.setCosmetic(true);
    bounding_box_pen_.setJoinStyle(Qt::RoundJoin);
    bounding_box_pen_.setCapStyle(Qt::RoundCap);
    bounding_box_pen_.setStyle(Qt::DashLine);
}

void ADrawableBase::setLayer(int layer)
{
    //TODO probably need some better logic here
    layer_ = layer;

    emit layerChanged(layer);
}

void ADrawableBase::drawBoundingBox(QPainter *painter)
{
    if (nullptr == painter) return;

    painter->setPen(bounding_box_pen_);
    painter->setBrush(Qt::NoBrush);

    painter->drawRect(boundingRect());
}

void ADrawableBase::encode(AJsonObject &data) const
{
    AndromedaObject::encode(data);

    // Layer
    data[OBJ_KEY::ITEM_LAYER] = layer();

    // Position
    data.addPoint(OBJ_KEY::POS, pos());
}

void ADrawableBase::decode(AJsonObject &data, bool undoable)
{
    AndromedaObject::decode(data, undoable);

    QPointF point;

    if (data.getPoint(OBJ_KEY::POS, point))
        setPos(point);

    //TODO
}

void ADrawableBase::setPos(QPointF point)
{
    // Ignore the same position
    if (point == pos()) return;

    //TODO - remove hard coded action title
    setUndoAction("Move",
                  OBJ_KEY::POS,
                  AJsonObject::fromPoint(pos()),
                  AJsonObject::fromPoint(point));

    QGraphicsItem::setPos(point);
}

void ADrawableBase::setPos(double x, double y)
{
    setPos(QPointF(x,y));
}

void ADrawableBase::setX(double x)
{
    setPos(x, this->y());
}

void ADrawableBase::setY(double y)
{
    setPos(this->x(), y);
}
