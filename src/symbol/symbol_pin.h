#ifndef SYMBOL_PIN_H
#define SYMBOL_PIN_H

#include "src/drawable/drawable_primitive.h"

class ASymbolPin : public ADrawablePrimitive
{
    Q_OBJECT

public:
    ASymbolPin(QObject *parent = 0);

    // Clone operator
    virtual ASymbolPin* clone(void) { return makeClone<ASymbolPin>(); }

    Q_PROPERTY( QString label READ label WRITE setLabel )
    Q_PROPERTY( double length READ length WRITE setLength )
    Q_PROPERTY( unsigned int orientation READ orientation WRITE setOrientation )

    /**
     * @brief The Orientation enum lists allowable pin orientations
     * The orientations describe the location of the connection point
     * e.g. LEFT means that that connection occurs at the left-most point of the pin
     */
    enum class Orientation : int {
        LEFT = 0,   // Pin connection point on the left
        DOWN,
        RIGHT,
        UP,
        INVALID,
    };

    // Property getters
    QString label(void) const   { return label_; }
    double length(void) const   { return length_; }
    unsigned orientation(void) const { return orientation_; }

    // JSON data
    virtual void encode(AJsonObject &data) const;
    virtual void decode(AJsonObject &data, bool undoable = true);

    // Drawing function
    QRectF boundingRect(void) const Q_DECL_OVERRIDE;
    QPainterPath shape(void) const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

public slots:
    void setLabel(QString label);
    void setLength(double length);
    void setOrientation(unsigned int orientation);
    void rotate(bool ccw = true);
    QPointF endPoint(void) const;
    QPointF endDelta(void) const;

protected:
    // The pin label
    QString label_;
    // Pin length
    double length_ = 100; //TODO - define a default length
    // Pin orientation
    unsigned int orientation_ = (int) Orientation::LEFT;

};

#endif // SYMBOL_PIN_H

