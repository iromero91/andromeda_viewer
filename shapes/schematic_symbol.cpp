#include <QJsonArray>

#include "schematic_symbol.h"

ASchematicSymbol::ASchematicSymbol(QObject *parent) : ADrawableComplex(parent)
{
    setObjectName(OBJECT_NAME::A_SCHEMATIC_SYMBOL);
}

ASchematicSymbol::~ASchematicSymbol()
{
    deletePins();
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
    ASymbolPin *newPin = new ASymbolPin();

    // A pin model was passed in - perform a COPY of ths pin
    if (nullptr != pin)
    {
        newPin->copyFrom(pin);
    }

    //TODO perform some checks on the pin here

    pins_.append(newPin);

    return newPin;
}

void ASchematicSymbol::encode(QJsonObject &json) const
{
    ADrawableComplex::encode(json);

    // Encode all the pins
    QJsonArray jPins;

    foreach (ASymbolPin *pin, pins_)
    {
        if (nullptr == pin) continue;

        jPins.append(pin->encoded());
    }

    json[JSON_KEY::PINS] = jPins;
}

void ASchematicSymbol::decode(QJsonObject &json)
{
    ADrawableComplex::decode(json);
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
