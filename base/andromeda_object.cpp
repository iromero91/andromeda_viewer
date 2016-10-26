#include "andromeda_object.h"

AndromedaObject::AndromedaObject(QObject *parent) : QObject(parent)
{

}

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
