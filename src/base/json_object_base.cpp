#include "json_object_base.h"

AJsonCloneableObject::AJsonCloneableObject(QObject *parent) : QObject(parent)
{
    setObjectName(OBJECT_NAME::A_JSON_OBJECT);
}

/**
 * @brief AJsonCloneableObject::encoded
 * Encode this object to JSON
 * @return a QJsonObject
 */
QJsonObject AJsonCloneableObject::encoded() const
{
    QJsonObject json;

    encode(json);

    return json;
}

/**
 * @brief AJsonCloneableObject::encodedString
 * Encodde this object to a JSON string
 * @return a string representation of the JSON object
 */
QString AJsonCloneableObject::encodedString() const
{
    QJsonObject json = encoded();
    QJsonDocument doc(json);

    return doc.toJson(); // QJsonDocument::Compact);
}

/**
 * @brief AJsonCloneableObject::encodedRaw
 * Return a binary encoding of the JSON object
 * @return
 */
QByteArray AJsonCloneableObject::encodedRaw() const
{
    QJsonObject json = encoded();
    QJsonDocument doc(json);

    return doc.toBinaryData();
}
