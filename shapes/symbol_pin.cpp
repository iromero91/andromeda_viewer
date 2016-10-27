#include "symbol_pin.h"

ASymbolPin::ASymbolPin(QObject *parent) : ADrawablePrimitive(parent)
{
    setObjectName(OBJECT_NAME::A_DRAWABLE_SYMBOL_PIN);
}

void ASymbolPin::encode(QJsonObject &json) const
{
    ADrawablePrimitive::encode(json);
}

void ASymbolPin::decode(QJsonObject &json)
{
    ADrawablePrimitive::decode(json);
}

void ASymbolPin::setName(QString name)
{
    //TODO better logic here
    name_ = name;
}

void ASymbolPin::setLength(double length)
{
    //TODO better logic here (min / max length, etc)
    length_ = fabs(length);
}

void ASymbolPin::setOrientation(int orientation)
{
    switch (orientation)
    {
    case (int) Orientation::LEFT:
    case (int) Orientation::DOWN:
    case (int) Orientation::RIGHT:
    case (int) Orientation::UP:
        orientation_ = orientation;
        break;
    default:
        break;
    }
}

void ASymbolPin::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(widget);

    if (nullptr == painter || nullptr == option) return;
}
