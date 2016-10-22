#ifndef SYMBOL_EDITOR_VIEW_H
#define SYMBOL_EDITOR_VIEW_H

#include "andromeda_view.h"

class SymbolEditorView : public AndromedaView
{
    Q_OBJECT

public:
    SymbolEditorView(QWidget * parent = 0);

protected:
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseDoubleClickEvent(QMouseEvent *event);
    void keyPressEvent(QKeyEvent *event);

    void drawForeground(QPainter *painter, const QRectF &rect);

    QList<LWPolyline*> lines_;
    LWPolyline tmpLine_;
    void startLine(QPointF pos);
    void addLinePoint(QPointF pos);
    void finishLine(QPointF pos);
    void addLineToScene();
    void cancelLine();

    // Actions available for the symbol editor view
    enum SymbolViewerActions
    {
        //TODO - these are just hacks
        //TODO - Implement an "action stack"
        // e.g. pressing 'escape' pops the top action from the stack for multi-sequence actions
        // selecting a new tool clears the action stack
        VIEW_ACTION_DRAW_LINE = 0x10000,
        VIEW_ACTION_ADD_CURVE,
    };

};

#endif // SYMBOL_EDITOR_VIEW_H

