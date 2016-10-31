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

    // Paint functions
    QRectF boundingRect() const Q_DECL_OVERRIDE;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    QPainterPath shape() const;


    // Property getters
    int pinCount(void) const { return pins_.count(); }
    QString name(void) const { return name_; }

    virtual void encode(AJsonObject &data) const;
    virtual void decode(AJsonObject &data, bool undoable = true);

public slots:
    ASymbolPin* addPin(ASymbolPin *pin = nullptr);
    void setName(QString name) { name_ = name; }

signals:

protected:
    QList<ASymbolPin*> pins_;

    // Reference Designator
    QString ref_des_;

    // Symbol Name
    QString name_;

    void updatePins(void);
    void deletePins(void);
};

#endif // SCHEMATIC_SYMBOL_H

