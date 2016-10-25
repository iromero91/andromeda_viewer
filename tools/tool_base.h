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
    AToolBase(QObject *parent = 0);

    bool isActive(void) { return (tool_state_ > TOOL_STATE::INACTIVE); }

    TOOL_STATE getToolState(void) { return tool_state_; }
    void setToolState(TOOL_STATE state) { tool_state_ = state; }

    virtual void paint(QPainter *painter, const QRectF &rect);

    virtual bool onMousePress(QMouseEvent *event, QPointF cursorPos);
    virtual bool onMouseRelease(QMouseEvent *event, QPointF cursorPos);
    virtual bool onMouseMove(QPointF cursorPos);
    virtual bool onMouseDoubleClick(QMouseEvent *event, QPointF cursorPos);

    virtual bool onKeyPress(QKeyEvent *event);
    virtual bool onKeyRelease(QKeyEvent *event);

    void setToolPos(QPointF pos) { tool_pos_ = pos; }
    QPointF getToolPos() { return tool_pos_; }

public slots:
    // Do not override these in any subclasses
    void start(void);
    void stop(void);
    void cancel(void);
    void reset(void);
    void finish(void);

signals:
    void finished(void);
    void cancelled(void);
    void updated(void);

protected:
    // Tool state machine
    TOOL_STATE tool_state_ = TOOL_STATE::INACTIVE;

    // Current tool position
    QPointF tool_pos_;

    // Overridable callbacks
    virtual void onStart(void)      {}
    virtual void onStop(void)       {}
    virtual void onCancel(void)     {}
    virtual void onReset(void)      {}
    virtual void onFinish(void)     {}

    void defaultPen(void);
    void defaultBrush(void);
};

#endif // TOOL_BASE_H

