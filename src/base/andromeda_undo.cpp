#include "andromeda_undo.h"

#include <QStringList>

AndromedaJsonUndoAction::AndromedaJsonUndoAction(QString text,
                                                 AJsonCloneableObject *object,
                                                 QJsonObject jBefore,
                                                 QJsonObject jAfter) : QUndoCommand(text)
{
    setText(text);

    object_ = object;

    QJsonDocument doc;

    doc.setObject(jBefore);
    before_ = doc.toBinaryData();

    doc.setObject(jAfter);
    after_ = doc.toBinaryData();
}

/**
 * @brief AndromedaJsonUndoAction::undo
 * UNDO this action
 */
void AndromedaJsonUndoAction::undo()
{
    if (nullptr == object_) return;

    QJsonObject jBefore = before();

    object_->decode(jBefore, false);
}

/**
 * @brief AndromedaJsonUndoAction::redo
 * REDO this action
 */
void AndromedaJsonUndoAction::redo()
{
    if (nullptr == object_) return;

    QJsonObject jAfter = after();

    object_->decode(jAfter, false);
}

QJsonObject AndromedaJsonUndoAction::before() const
{
    QJsonDocument jDoc = QJsonDocument::fromBinaryData(before_);

    QJsonObject jObj;

    if (!jDoc.isNull())
    {
        jObj = jDoc.object();
    }

    return jObj;
}

QJsonObject AndromedaJsonUndoAction::after() const
{
    QJsonDocument jDoc = QJsonDocument::fromBinaryData(after_);

    QJsonObject jObj;

    if (!jDoc.isNull())
    {
        jObj = jDoc.object();
    }

    return jObj;
}

/**
 * @brief AndromedaJsonUndoAction::mergeWith
 * Merge a new JSON undo action with an old one
 * Values from the NEW action override old values if there are duplicate values
 * @param other is a po
 */
bool AndromedaJsonUndoAction::mergeWith(const QUndoCommand *other)
{
    // Ensure we are looking at another JSONable action
    AndromedaJsonUndoAction *aOther = const_cast<AndromedaJsonUndoAction*>(reinterpret_cast<const AndromedaJsonUndoAction*>(other));

    if (nullptr == aOther)
        return false;

    // Actions must point to the same object
    if (aOther->object() != this->object())
        return false;

    // Extract the AFTER JSON objects
    QJsonObject jThis = after();
    QJsonObject jOther = aOther->after();

    // Copy across the data
    foreach (QString key, jOther.keys())
    {
        jThis[key] = jOther.value(key);
    }

    return true;

}
