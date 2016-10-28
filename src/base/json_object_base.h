#ifndef JSON_OBJECT_BASE_H
#define JSON_OBJECT_BASE_H

#include <QObject>
#include <QJsonObject>
#include <QJsonDocument>

#include "object_names.h"

/**
 * @brief The AJsonCloneableObject class is an object
 * which provides JSON encode/decode functions that can be used for:
 * - Object serialization
 * - Object copying / cloning
 * - UNDO / REDO commands
 * - Diff inspection
 *
 * This is the base class for AndromedaObject.
 *
 * All encode/decode functions are virtual and should be reimplemented
 * as required in derived classes
 */
class AJsonCloneableObject : public QObject
{
    Q_OBJECT

public:
    AJsonCloneableObject(QObject *parent = 0);
    virtual ~AJsonCloneableObject(void) {}

    // virtual JSON serialization functions
    virtual void decode(QJsonObject &json, bool undoable = true)       { Q_UNUSED(json); Q_UNUSED(undoable) }
    virtual void encode(QJsonObject &json) const { Q_UNUSED(json); }

    virtual QJsonObject encoded(void)   const;
    virtual QByteArray encodedRaw(void) const;
    virtual QString encodedString(void) const;
};

#endif // JSON_OBJECT_BASE_H

