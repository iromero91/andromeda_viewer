#ifndef SYMBOL_PIN_H
#define SYMBOL_PIN_H

#include "src/drawable/drawable_primitive.h"

class ASymbolPin : public ADrawablePrimitive
{
    Q_OBJECT

public:
    ASymbolPin(QObject *parent = 0);

    Q_PROPERTY( QString label READ label WRITE setLabel )
    Q_PROPERTY( double length READ length WRITE setLength )
    Q_PROPERTY( int orientation READ orientation WRITE setOrientation )

    /**
     * @brief The Orientation enum lists allowable pin orientations
     * The orientations describe the location of the connection point
     * e.g. LEFT means that that connection occurs at the left-most point of the pin
     */
    enum class Orientation : int {
        LEFT = 0,
        DOWN,
        RIGHT,
        UP,
        INVALID,
    };

    // Property getters
    QString label(void) const   { return label_; }
    double length(void) const   { return length_; }
    int orientation(void) const { return orientation_; }

    // JSON data
    virtual void encode(QJsonObject &json) const;
    virtual void decode(QJsonObject &json);

    // Drawing function
    QRectF boundingRect(void) const Q_DECL_OVERRIDE;
    QPainterPath shape(void) const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

public slots:
    void setLabel(QString label);
    void setLength(double length);
    void setOrientation(int orientation);
    void rotate(bool ccw = true);

protected:
    // The pin label
    QString label_;
    // Pin length
    double length_ = 100; //TODO - define a default length
    // Pin orientation
    int orientation_ = (int) Orientation::LEFT;

};

#endif // SYMBOL_PIN_H

