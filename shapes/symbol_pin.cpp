#include "symbol_pin.h"

ASymbolPin::ASymbolPin(QObject *parent) : ADrawablePrimitive(parent)
{
    setObjectName(OBJECT_NAME::A_DRAWABLE_SYMBOL_PIN);
}

void ASymbolPin::encode(QJsonObject &json) const
{
    ADrawablePrimitive::encode(json);

    json[JSON_KEY::LABEL] = label();
    json[JSON_KEY::LENGTH] = length();
    json[JSON_KEY::ORIENTATION] = orientation();
}

void ASymbolPin::decode(QJsonObject &json)
{
    ADrawablePrimitive::decode(json);

    // Extract pin data (use current values in case of bad data)
    if (json.contains(JSON_KEY::LABEL))
        setLabel(json.value(JSON_KEY::LABEL).toString(label()));

    if (json.contains(JSON_KEY::LENGTH))
        setLength(json.value(JSON_KEY::LABEL).toDouble(length()));

    if (json.contains(JSON_KEY::ORIENTATION))
        setOrientation(json.value(JSON_KEY::ORIENTATION).toInt(orientation()));
}

void ASymbolPin::setLabel(QString label)
{
    //TODO better logic here
    label_ = label;
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
