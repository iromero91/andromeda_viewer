#ifndef SYMBOL_EDITOR_VIEW_H
#define SYMBOL_EDITOR_VIEW_H

#include "andromeda_view.h"

#include "shapes/polyline.h"
#include "shapes/ellipse.h"
#include "shapes/rect.h"

#include "tools/polyline_tool.h"

class SymbolEditorView : public AView
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

    // Polyline tool
    PolylineDrawingTool poly_tool_;
};

#endif // SYMBOL_EDITOR_VIEW_H

