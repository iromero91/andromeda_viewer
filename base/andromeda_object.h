#ifndef ANDROMEDA_OBJECT_H
#define ANDROMEDA_OBJECT_H

#include <QObject>
#include <QStringList>

#include <QMetaObject>
#include <QMetaProperty>

/**
 * @brief The AndromedaObject class
 * This is designed to be the base class of "any" andromeda object
 * e.g. pins,
 */

class AndromedaObject : public QObject
{
    Q_OBJECT

public:
    AndromedaObject(QObject *parent = 0);

    QList<QMetaProperty> getProperties(void);
    QStringList getPropertyNames(void);

};

#endif //ANDROMEDA_OBJECT_H
