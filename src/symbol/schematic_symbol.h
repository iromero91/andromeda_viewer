#ifndef SCHEMATIC_SYMBOL_H
#define SCHEMATIC_SYMBOL_H

#include <memory>

#include "src/drawable/drawable_complex.h"

#include "symbol_pin.h"

class ASchematicSymbol : public ADrawableComplex
{
    Q_OBJECT

    Q_PROPERTY( QString name READ name WRITE setName )
    Q_PROPERTY( QString ref READ ref WRITE setRef )
    Q_PROPERTY( int pinCount READ pinCount STORED false )
    Q_PROPERTY( int symbolCount READ symbolCount WRITE setSymbolCount )

public:
    ASchematicSymbol(QObject *parent = 0);
    virtual ~ASchematicSymbol(void);

    // Paint functions
    QRectF boundingRect() const Q_DECL_OVERRIDE;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    QPainterPath shape() const;

    // Property getters
    int pinCount(void) const { return pins_.count(); }
    QString name(void) const { return name_; }
    QString ref(void) const { return ref_des_; }
    unsigned char symbolCount(void) { return symbol_count_; }

    virtual void encode(AJsonObject &data) const;
    virtual void decode(AJsonObject &data, bool undoable = true);

public slots:
    ASymbolPin* addPin(void);
    ASymbolPin* addPin(ASymbolPin *pin);
    ASymbolPin* addPin(AJsonObject data);
    void setName(QString name) { name_ = name; }
    void setRef(QString ref);
    void setSymbolCount(unsigned char count);

signals:

protected:
    //TODO - make use of proper smart pointers
    QList<ASymbolPin*> pins_;

    // Reference Designator
    QString ref_des_ = "U";

    // Symbol Name
    QString name_ = "Symbol";

    // Number of sub-symbols
    unsigned char symbol_count_ = 1;

    void updatePins(void);
    void deletePins(void);
};

#endif // SCHEMATIC_SYMBOL_H

