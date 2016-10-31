#include "symbol_pin.h"

ASymbolPin::ASymbolPin(QObject *parent) : ADrawablePrimitive(parent)
{
    setObjectName(OBJECT_NAME::A_DRAWABLE_SYMBOL_PIN);
}

void ASymbolPin::encode(AJsonObject &data) const
{
    ADrawablePrimitive::encode(data);

    data[OBJ_KEY::LABEL] = label();
    data[OBJ_KEY::LENGTH] = length();
    data[OBJ_KEY::ORIENTATION] = orientation();
}

void ASymbolPin::decode(AJsonObject &data, bool undoable)
{
    ADrawablePrimitive::decode(data, undoable);

    QString text;
    double d;
    int i;

    // Extract pin label
    if (data.getString(OBJ_KEY::LABEL, text))
    {
        setLabel(text);
    }

    if (data.getDouble(OBJ_KEY::LENGTH, d))
    {
        setLength(d);
    }

    if (data.getInt(OBJ_KEY::ORIENTATION, i))
    {
        setOrientation(i);
    }
}

void ASymbolPin::setLabel(QString label)
{
    // Ignore same value
    if (label == label_) return;

    //TODO better logic here
    label_ = label;

    prepareGeometryChange();
}

void ASymbolPin::setLength(double length)
{
    // Ignore same value
    if (length == length_) return;

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
    // Ignore same value
    if (orientation == orientation_) return;

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
