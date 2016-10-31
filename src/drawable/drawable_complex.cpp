#include "drawable_complex.h"

ADrawableComplex::ADrawableComplex(QObject *parent) : ADrawableBase(parent)
{
    setObjectName(OBJECT_NAME::A_DRAWABLE_COMPLEX);
}

void ADrawableComplex::encode(QJsonObject &json) const
{
    ADrawableBase::encode(json);

    // Flipped nature of this object
    if (flip() != (int) Flip::NONE)
    {
        json[OBJ_KEY::FLIP] = flip();
    }
    else
    {
        json.remove(OBJ_KEY::FLIP);
    }

}

void ADrawableComplex::decode(QJsonObject &json, bool undoable)
{
    ADrawableBase::decode(json, undoable);

    if (json.value(OBJ_KEY::FLIP).isDouble())
        setFlip(json.value(OBJ_KEY::FLIP).toInt(flip()));
}

void ADrawableComplex::setFlip(int flip)
{
    if ((flip >= (int) Flip::NONE) && (flip <= (int) Flip::BOTH))
    {
        flip_ = flip;
    }
}
