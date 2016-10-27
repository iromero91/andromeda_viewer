#include "drawable_complex.h"

ADrawableComplex::ADrawableComplex(QObject *parent) : ADrawableBase(parent)
{
    setObjectName(OBJECT_NAME::A_DRAWABLE_COMPLEX);
}

void ADrawableComplex::encode(QJsonObject &json) const
{
    ADrawableBase::encode(json);
}

void ADrawableComplex::decode(QJsonObject &json)
{
    ADrawableBase::decode(json);
}
