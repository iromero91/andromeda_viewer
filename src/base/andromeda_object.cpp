#include "andromeda_object.h"

AndromedaObject::AndromedaObject(QObject *parent) : QObject(parent)
{
    setObjectName(OBJECT_NAME::A_OBJECT);
}

/**
 * @brief AndromedaObject::getProperties
 * @return a list of QMetaProperty objects associated with this AndromedaObject
 */
QList<QMetaProperty> AndromedaObject::getProperties()
{
    QList<QMetaProperty> props;

    const QMetaObject *object = metaObject();

    if (nullptr == object)
        return props;

    QMetaProperty prop;

    for (int i=0; i<object->propertyCount(); i++)
    {
        prop = object->property(i);

        props.append(prop);
    }

    return props;
}

/**
 * @brief AndromedaObject::getPropertyNames
 * @return a list of the property names associated with this object
 */
QStringList AndromedaObject::getPropertyNames()
{
    QList<QMetaProperty> props = getProperties();

    QStringList names;

    foreach (QMetaProperty p, props)
    {
        names.append(QString::fromUtf8(p.name()));
    }

    return names;
}

QJsonObject AndromedaObject::encoded() const
{
    QJsonObject json;

    encode(json);

    return json;
}

QString AndromedaObject::encodedString() const
{
    QJsonObject json = encoded();
    QJsonDocument doc(json);

    return doc.toJson(QJsonDocument::Compact);
}

/**
 * @brief AndromedaObject::copyFrom
 * Copy the properties from <other> object to <this> object (via JSON)
 * Any compatible properties will be applied to <this>
 * @param other is a pointer to <other> AndromedaObject
 */
void AndromedaObject::copyFrom(AndromedaObject *other)
{
    if (nullptr == other) return;

    QJsonObject json = other->encoded();

    decode(json);
}

/**
 * @brief AndromedaObject::copyTo
 * Copy the properties from <this> object to <other> object (via JSON)
 * @param other is a pointer to <other> AndromedaObject
 */
void AndromedaObject::copyTo(AndromedaObject *other)
{
    if (nullptr == other) return;

    QJsonObject json = encoded();

    other->decode(json);
}
