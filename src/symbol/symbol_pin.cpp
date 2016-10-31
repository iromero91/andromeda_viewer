#include "symbol_pin.h"

#include "src/geometry/bounding_box.h"

#include <QDebug>

ASymbolPin::ASymbolPin(QObject *parent) : ADrawablePrimitive(parent)
{
    setObjectName(OBJECT_NAME::A_DRAWABLE_SYMBOL_PIN);
}

void ASymbolPin::encode(AJsonObject &data) const
{
    ADrawablePrimitive::encode(data);

    data[OBJ_KEY::LABEL] = label();
    data[OBJ_KEY::LENGTH] = length();
    data[OBJ_KEY::ORIENTATION] = (int) orientation();
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

    //TODO - apply inverse action

    //TODO better logic here
    label_ = label;

    prepareGeometryChange();
}

void ASymbolPin::setLength(double length)
{
    // Ignore same value
    if (length == length_) return;

    //TODO - apply inverse action

    //TODO better logic here (min / max length, etc)
    length_ = qAbs(length);

    prepareGeometryChange();
}

/**
 * @brief ASymbolPin::rotate
 * Rotates the pin in the specified direction
 * @param ccw is bool, true = counter-clockwise (default), false = clockwise
 */
void ASymbolPin::rotate(bool ccw)
{
    unsigned int orient = orientation();

    orient += ccw ? 1 : -1;

    orient = (orient % (int) Orientation::INVALID);

    setOrientation(orient);
}

void ASymbolPin::setOrientation(unsigned int orientation)
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
        //TODO - apply inverse action
        orientation_ = orientation;
        break;
    default:
        // Invalid
        return;
    }

    prepareGeometryChange();
}

QPointF ASymbolPin::endDelta() const
{

    double dx, dy;

    switch (orientation_)
    {
    default:
    case (int) Orientation::LEFT:
        dx = length_;
        dy = 0;
        break;
    case (int) Orientation::DOWN:
        dx = 0;
        dy = length_;
        break;
    case (int) Orientation::RIGHT:
        dx = -length_;
        dy = 0;
        break;
    case (int) Orientation::UP:
        dx = 0;
        dy = -length_;
        break;
    }

    return QPointF(dx, dy);
}

QPointF ASymbolPin::endPoint() const
{
    return pos() + endDelta();
}

void ASymbolPin::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(widget);

    if (nullptr == painter || nullptr == option) return;

    QPen p(QColor(170,20,50));
    p.setCapStyle(Qt::RoundCap);
    p.setJoinStyle(Qt::RoundJoin);
    p.setStyle(Qt::DotLine);

    painter->setPen(p);
    painter->setBrush(Qt::NoBrush);

    painter->drawEllipse(QPointF(0,0), 10, 10);

    p.setWidth(5);
    p.setStyle(Qt::SolidLine);

    painter->setPen(p);

    painter->drawLine(QPointF(), endDelta());
}

QRectF ASymbolPin::boundingRect() const
{
    ABoundingBox b(QPointF(0,0));

    b.add(endDelta());

    b.expand(12);

    return b.normalized();
}

QPainterPath ASymbolPin::shape() const
{
    QPainterPath path;
    //TODO

    path.addRect(boundingRect());

    return path;
}
