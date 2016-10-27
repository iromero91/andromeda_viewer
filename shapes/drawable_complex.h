#ifndef DRAWABLE_COMPLEX_H
#define DRAWABLE_COMPLEX_H

#include "drawable_base.h"

/**
 * @brief The ADrawableComplex class describes complex shapes which can be made up of (multiple) simpler shapes
 * e.g. schematic symbols, pcb footprints, etc
 */
class ADrawableComplex : public ADrawableBase
{
    Q_OBJECT

public:
    ADrawableComplex(QObject *parent = 0);

    void encode(QJsonObject &json) const;
    void decode(QJsonObject &json);
};


#endif // DRAWABLE_COMPLEX_H

