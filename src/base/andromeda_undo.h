#ifndef ANDROMEDA_UNDO_H
#define ANDROMEDA_UNDO_H

#include <QUndoCommand>
#include <QJsonObject>

/**
 * @brief The AndromedaJsonUndoAction class
 * This class provides AndromedaObject undo/redo functionality via the JSON serialization
 * JSON objects are compressed to QByteArray for reduced memory requirements
 *
 * Each command stores the state of the AndromedaObject BEFORE the action is applied
 * (expressed as a JSON representation of the object)
 *
 * The granularity of the action is controlled by the JSON passed to the command.
 *
 * e.g. a single parameter can be altered by only adding THAT parameter to the JSON data
 *
 * Alternatively, multiple parameters can be changed in a single undo/redo commit
 *
 * Multiple commands can be compressed together by merging the JSON data
 * (with NEWER values overriding the OLDER ones)
 *
 */
class AndromedaJsonUndoAction : public QUndoCommand
{
public:
    AndromedaJsonUndoAction(QString text, QJsonObject jBefore, QJsonObject jAfter);

protected:
    QByteArray before_;
    QByteArray after_;
};

#endif // ANDROMEDA_UNDO_H

