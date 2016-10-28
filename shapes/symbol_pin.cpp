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

    prepareGeometryChange();
}

void ASymbolPin::setLength(double length)
{
    //TODO better logic here (min / max length, etc)
    length_ = fabs(length);

    prepareGeometryChange();
}

/**
 * @brief ASymbolPin::rotate
 * Rotates the pin in the specified direction
 * @param ccw is bool, true = counter-clockwise (default), false = clockwise
 */
void ASymbolPin::rotate(bool ccw)
{
    int orient = orientation();

    orient += ccw ? 1 : -1;

    orient = (orient % (int) Orientation::INVALID);

    setOrientation(orient);
}

void ASymbolPin::setOrientation(int orientation)
{
    //TODO - some more complex functionality here?
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

    prepareGeometryChange();
}

void ASymbolPin::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(widget);

    if (nullptr == painter || nullptr == option) return;

    //TODO
}

QRectF ASymbolPin::boundingRect() const
{
    QRectF rect;
    //TODO

    return rect;
}

QPainterPath ASymbolPin::shape() const
{
    QPainterPath path;
    //TODO

    return path;
}
