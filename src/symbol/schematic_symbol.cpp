#include <QJsonArray>
#include <QDebug>

#include "schematic_symbol.h"

ASchematicSymbol::ASchematicSymbol(QObject *parent) : ADrawableComplex(parent)
{
    setObjectName(OBJECT_NAME::A_SCHEMATIC_SYMBOL);
}

ASchematicSymbol::~ASchematicSymbol()
{
    deletePins();
}

void ASchematicSymbol::setSymbolCount(unsigned char count)
{
    // Ignore invalid values
    if ((count == 0) || (count == symbol_count_)) return;

    //TODO - Apply undo action
    symbol_count_ = count;
}

void ASchematicSymbol::setRef(QString ref)
{
    if (ref == ref_des_) return;

    //TODO - apply undo action
    ref_des_ = ref;
}

/**
 * @brief ASchematicSymbol::addPin
 * Add a new pin from a JSON dataset
 * @param data
 * @return
 */
ASymbolPin* ASchematicSymbol::addPin(AJsonObject data)
{
    // Make a new pin as a child of this symbol
    //TODO - make this a smart pointer
    ASymbolPin *pin = new ASymbolPin(this);

    // Decode pin data and prevent undo
    pin->decode(data, false);

    pins_.append(pin);

    // Add pin as a child of the graphics object
    pin->setParentItem(this);

    prepareGeometryChange();
    update();

    return pin;
}

/**
 * @brief ASchematicSymbol::addPin
 * Attempt to add a new pin to this symbol. A pre-formed pin can be passed as an argument
 * If the supplied pin is nullptr then a new blank pin will be aded
 * @param pin is a pointer to the pin to be added
 * @return a pointer to the created pin
 */
ASymbolPin* ASchematicSymbol::addPin(ASymbolPin *pin)
{
    if (nullptr == pin) return nullptr;

    // Copy the encoded pin data
    return addPin(pin->encoded());
}

ASymbolPin* ASchematicSymbol::addPin()
{
    return addPin(new ASymbolPin());
}

void ASchematicSymbol::encode(AJsonObject &data) const
{
    ADrawableComplex::encode(data);

    // Encode the name of the symbol
    data[OBJ_KEY::NAME] = name_;
    data[OBJ_KEY::REF] = ref_des_;
    data[OBJ_KEY::SYMBOLS] = symbol_count_;

    // Encode all the pins
    QJsonArray jPins;

    foreach (ASymbolPin *pin, pins_)
    {
        if (nullptr == pin) continue;

        jPins.append(pin->encoded());
    }

    data[OBJ_KEY::PINS] = jPins;
}

void ASchematicSymbol::decode(AJsonObject &data, bool undoable)
{
    ADrawableComplex::decode(data, undoable);

    QString string;

    if (data.getString(OBJ_KEY::NAME, string))
        setName(string);

    if (data.getString(OBJ_KEY::REF, string))
        setRef(string);

    // TODO
}

/**
 * @brief ASchematicSymbol::updatePins
 * Perform 'cleanup' operations on each pin
 *
 */
//TODO for now all this does is delete nullptrs
void ASchematicSymbol::updatePins()
{
    int index = 0;

    while (index < pins_.count())
    {
        if (nullptr == pins_.at(index))
        {
            pins_.removeAt(index);
            continue;
        }

        // Move on to the next pin
        index++;
    }
}

void ASchematicSymbol::deletePins()
{
    qDeleteAll(pins_.begin(), pins_.end());
    pins_.clear();
}

QRectF ASchematicSymbol::boundingRect() const
{
    return bounding_box_;
}

void ASchematicSymbol::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    //TODO
}

QPainterPath ASchematicSymbol::shape() const
{
    return shape_;
}
