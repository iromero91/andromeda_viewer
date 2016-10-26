#ifndef ANDROMEDA_OBJECT_H
#define ANDROMEDA_OBJECT_H

#include <QObject>

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

};

#endif //ANDROMEDA_OBJECT_H
