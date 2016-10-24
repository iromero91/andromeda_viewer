#ifndef DRAWING_TOOL_H
#define DRAWING_TOOL_H

/*
 * Drawing tools are used to handle sequential drawing steps.
 * Each drawing tool keeps an internal state machine and handles the specifics of its own drawing
 * The drawing tool gets added to the scene
 */

#include <QGraphicsObject>
#include <QPen>
#include <QBrush>

#include "tool_defines.h"

class ADrawingTool : public QGraphicsObject
{
    Q_OBJECT

public:
    ADrawingTool();

    int getToolState(void) { return tool_state_; }
    void setToolState(int state) { tool_state_ = state; }

    void setPen(QPen pen) { tool_pen_ = pen; }
    void setBrush(QBrush brush) { tool_brush_ = brush; }

    QPen getPen() { return tool_pen_; }
    QBrush getBrush() { return tool_brush_; }

public slots:
    // Reset the tool to a neutral state
    virtual void reset(void) = 0;

    // Start the tool (no position provided)
    virtual void start(void) = 0;

    // Start the tool at the provided position
    virtual void start(QPointF pos) = 0;

    // Update the tool position as the mouse moves
    void update(QPointF pos);

    // Add a new point to the tool
    virtual void addPoint(QPointF point) = 0;

    // Finish the tool
    virtual void finish(void) = 0;

    // Cancel the tool
    void cancel(void);

signals:
    void started(void);
    void finished(void);
    void cancelled(void);

protected:
    // Tool state machine
    int tool_state_;

    // Current tool position
    QPointF tool_pos_;

    QPen tool_pen_;
    QBrush tool_brush_;

    void defaultPen(void);
    void defaultBrush(void);

    // Called by finish() and cancel()
    void clear(void);

    // Called from SLOT(update)
    virtual void onUpdate(void) = 0;
};

#endif // DRAWING_TOOL_H

