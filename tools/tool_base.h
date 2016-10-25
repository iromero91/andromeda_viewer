#ifndef TOOL_BASE_H
#define TOOL_BASE_H

#include <QDebug>

/*
 * Drawing tools are used to handle sequential drawing steps.
 * Each drawing tool keeps an internal state machine and handles the specifics of its own drawing
 * The drawing tool gets added to the scene
 */

#include <QObject>
#include <QPainter>
#include <QPen>
#include <QBrush>

#include <QMouseEvent>
#include <QKeyEvent>

#include "tool_defines.h"

class AToolBase : public QObject
{
    Q_OBJECT

public:
    AToolBase();

    bool isActive(void) { return tool_state_ != (int) TOOL_STATE::INACTIVE; }

    int getToolState(void) { return tool_state_; }
    void setToolState(int state) { tool_state_ = state; }

    void paint(QPainter *painter, const QRectF &rect);

public slots:
    // Reset the tool to a neutral state
    virtual void reset(void) = 0;

    // Start the tool (no position provided)
    virtual void start(void) = 0;

    // Finish the tool
    virtual void finish(void) = 0;

    // Cancel the tool
    void cancel(void);

    // Send events to the tool
    // Override these to implement
    bool onMousePress(QMouseEvent *event)       { Q_UNUSED(event); return false; }
    bool onMouseRelease(QMouseEvent *event)     { Q_UNUSED(event); return false; }
    bool onMouseMove(QMouseEvent *event)        { Q_UNUSED(event); return false; }
    bool onMouseDoubleClick(QMouseEvent *event) { Q_UNUSED(event); return false; }
    bool onKeyPress(QKeyEvent *event)           { Q_UNUSED(event); return false; }
    bool onKeyRelease(QKeyEvent *event)         { Q_UNUSED(event); return false; }

signals:
    void started(void);
    void finished(void);
    void cancelled(void);

protected:
    // Tool state machine
    int tool_state_;

    // Current tool position
    QPointF tool_pos_;

    void defaultPen(void);
    void defaultBrush(void);

    // Called by finish() and cancel()
    void clear(void);

    // Called from SLOT(update)
    void onUpdate(void);
};

#endif // TOOL_BASE_H

