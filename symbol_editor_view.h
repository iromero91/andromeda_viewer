#ifndef SYMBOL_EDITOR_VIEW_H
#define SYMBOL_EDITOR_VIEW_H

#include "andromeda_view.h"

#include "lwpolyline.h"
#include "andromeda_ellipse.h"
#include "andromeda_rect.h"

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
    void keyReleaseEvent(QKeyEvent *event);

    void drawForeground(QPainter *painter, const QRectF &rect);

    // LWPolyline creation
    LWPolyline tmpLine_;
    void lineMode();
    void startLine(QPointF pos);
    void addLinePoint(QPointF pos);
    void finishLine(QPointF pos);
    void addLine();

    // Add a temporary item for graphics creation
    void addTempItem(QGraphicsItem *item);

    // Rectangle creation
    AndromedaRect tmpRect_;
    void rectMode();
    void startRect(QPointF pos, double width = 0, double height = 0);
    void updateRect(QPointF pos);
    void addRect();
    void addRect(QPointF pStart, QPointF pEnd);
    void addRect(QPointF pStart, double width, double height);

    // Ellipse creation
    AndromedaEllipse tmpEllipse_;
    void ellipseMode();
    void setEllipseCenter(QPointF point);
    void setEllipseRadius(QPointF point);
    void addEllipse();
    void addEllipse(QPointF center, double radius);
    void addEllipse(QPointF center, double rx, double ry);

    // Actions available for the symbol editor view
    enum SymbolViewerActions
    {
        //TODO - these are just hacks
        //TODO - Implement an "action stack"
        // e.g. pressing 'escape' pops the top action from the stack for multi-sequence actions
        // selecting a new tool clears the action stack
        VIEW_ACTION_LINE_SET_START = 0x10000,
        VIEW_ACTION_LINE_ADD_POINT,

        VIEW_ACTION_ELLIPSE_SET_CENTER = 0x100010,
        VIEW_ACTION_ELLIPSE_SET_RADIUS,

        VIEW_ACTION_RECT_SET_START = 0x100020,
        VIEW_ACTION_RECT_SET_FINISH,
    };

    void onActionAdded(unsigned int action);
    void onActionCancelled(unsigned int action);
};

#endif // SYMBOL_EDITOR_VIEW_H

