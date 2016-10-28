#ifndef SCHEMATIC_SYMBOL_H
#define SCHEMATIC_SYMBOL_H

#include "src/drawable/drawable_complex.h"

#include "symbol_pin.h"

class ASchematicSymbol : public ADrawableComplex
{
    Q_OBJECT

    Q_PROPERTY( QString name READ name WRITE setName )
    Q_PROPERTY( int pinCount READ pinCount STORED false )

public:
    ASchematicSymbol(QObject *parent = 0);
    virtual ~ASchematicSymbol(void);


    // Property getters
    int pinCount(void) const { return pins_.count(); }
    QString name(void) const { return name_; }

    void encode(QJsonObject &json) const;
    void decode(QJsonObject &json);

public slots:
    ASymbolPin* addPin(ASymbolPin *pin = nullptr);
    void setName(QString name) { name_ = name; }

signals:

protected:
    QList<ASymbolPin*> pins_;
    QString name_;

    void updatePins(void);
    void deletePins(void);
};

#endif // SCHEMATIC_SYMBOL_H

