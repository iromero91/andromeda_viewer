#ifndef ANDROMEDA_OBJECT_H
#define ANDROMEDA_OBJECT_H

#include <QObject>
#include <QJsonObject>
#include <QDebug>

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

    virtual void readDataFromJson(QJsonObject *object)      { Q_UNUSED(object); }
    virtual void writeDataToJson(QJsonObject *object) const { Q_UNUSED(object); }

    // Default clone operator -> Override in child class using the same template pattern
    virtual AndromedaObject* clone(void) { return makeClone<AndromedaObject>(); }

protected:

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
     * @return
     */
    template <typename T>
    T* makeClone()
    {
        T* cloned = new T();

        QJsonObject *json = new QJsonObject();

        writeDataToJson(json);

        cloned->readDataFromJson(json);

        return static_cast<T*> (cloned);
    }
};

#endif //ANDROMEDA_OBJECT_H
