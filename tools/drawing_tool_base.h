#ifndef DRAWING_TOOL_H
#define DRAWING_TOOL_H

/*
 * Drawing tools are used to handle sequential drawing steps.
 * Each drawing tool keeps an internal state machine and handles the specifics of its own drawing
 */

#include <QGraphicsObject>

class AndromedaDrawingTool : public QGraphicsObject
{
public:
    AndromedaDrawingTool();

    // Add a 'point' to the tool (what the tool does with this WILL SHOCK YOU)
    virtual void addPoint(QPointF point) = 0;

    // Attempt to complete the tool action
    virtual bool finish(void) = 0;

    // Cancel the tool action
    virtual void cancel(void);

public slots:
    // TODO

signals:
    void cancelled();
    void finished();
    void started();

    // TODO

};

#endif // DRAWING_TOOL_H

