#ifndef ANDROMEDA_OBJECT_H
#define ANDROMEDA_OBJECT_H

#include <QObject>
#include <QStringList>
#include <QMetaObject>
#include <QMetaProperty>
#include <QJsonObject>
#include <QJsonDocument>

#include "json_keys.h"
#include "object_names.h"

/**
 * @brief The AndromedaObject class
 * This is designed to be the base class of "any" andromeda object
 * Each AndromedaObject should define functions for JSON serialization
 * The base AndromedaObject provides a makeClone() method which returns a new derived object
 * This object is loaded with parameters based on the JSON serialization
 * This allows a copy operator (which QObject prohibits) which will provide as much or as little functionality as the defined JSON operation
 */

class AndromedaObject : public QObject
{
    Q_OBJECT

public:
    AndromedaObject(QObject *parent = 0);
    virtual ~AndromedaObject(void) {}

    QList<QMetaProperty> getProperties(void);
    QStringList getPropertyNames(void);

    // Serialize this object data toJSON
    virtual QJsonObject encoded(void)   const;
    virtual QString encodedString(void) const;

    virtual void decode(QJsonObject &json)       { Q_UNUSED(json); }
    virtual void encode(QJsonObject &json) const { Q_UNUSED(json); }

    // Default clone operator -> Override in child class using the same template pattern
    virtual AndromedaObject* clone(void) { return makeClone<AndromedaObject>(); }


    /**
     * @brief makeClone
     * This templated function provides an explicit, consistent method of deep-copying an AndromedaObject
     * Instead of relying on the copy constructor of the object,
     * the makeClone() function relies on the inherent JSON serialization of the AndromedaObject class
     * (Note that the serialization is required for these objects, and we can easily leverage this existing functionality)
     *
     * If a non-JSON clone() is required for a particular class, then simply override the clone() function!
     *
     * To use the JSON deep-copy as below, e.g. for some arbitrary class called AChildClass:
     *
     * virtual AChildClass *clone() { return makeClone<AChildClass>(); }
     *
     * And that's all there is to it!
     *
     * Why do it this way?
     * 1. Consistency between object serialization and internal object state
     * 2. Allows cut / copy / paste operations to be performed on text data
     * 3. Allows undo / redo operations to be performed using the same data
     * 4. "Shallower" copies can be arbitrarily defined by excluding certain data from the JSON object
     * 5. It's always important to have a fifth reason
     *
     * @return
     */
    template <typename T>
    T* makeClone(void)
    {
        T* cloned = new T();

        QJsonObject json;

        encode(json);

        cloned->decode(json);

        return cloned;
    }

    // Copy functions
    void copyFrom(AndromedaObject *other);
    void copyTo(AndromedaObject *other);

protected:

};

#endif //ANDROMEDA_OBJECT_H
