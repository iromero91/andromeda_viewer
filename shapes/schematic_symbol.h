#ifndef SCHEMATIC_SYMBOL_H
#define SCHEMATIC_SYMBOL_H

#include "drawable_complex.h"
#include "symbol_pin.h"

class ALibrarySymbol : public ADrawableComplex
{
    Q_OBJECT

    Q_PROPERTY( int pinCount READ pinCount STORED false )

public:
    ASchematicSymbol(QObject *parent = 0);
    virtual ~ASchematicSymbol(void);

    ASymbolPin* addPin(ASymbolPin *pin = nullptr);

    // Property getters
    int pinCount(void) const { return pins_.count(); }

    void encode(QJsonObject &json) const;
    void decode(QJsonObject &json);

public slots:

signals:

protected:
    QList<ASymbolPin*> pins_;

    void updatePins(void);
    void deletePins(void);
};

#endif // SCHEMATIC_SYMBOL_H

