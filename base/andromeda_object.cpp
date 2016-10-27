#include "andromeda_object.h"

AndromedaObject::AndromedaObject(QObject *parent) : QObject(parent)
{
    setObjectName("AndromedaObject");
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

QJsonObject AndromedaObject::encode() const
{
    QJsonObject json;

    encode(&json);

    return json;
}

QString AndromedaObject::encodedString() const
{
    QJsonObject json = encode();
    QJsonDocument doc(json);

    return doc.toJson(QJsonDocument::Compact);
}
