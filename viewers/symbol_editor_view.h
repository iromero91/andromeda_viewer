#ifndef SYMBOL_EDITOR_VIEW_H
#define SYMBOL_EDITOR_VIEW_H

#include "andromeda_view.h"

#include "shapes/polyline.h"
#include "shapes/ellipse.h"
#include "shapes/rect.h"

#include "tools/polyline_drawing_tool.h"
#include "tools/ellipse_drawing_tool.h"
#include "tools/rect_drawing_tool.h"

class SymbolEditorView : public AView
{
    Q_OBJECT

public:
    SymbolEditorView(QWidget * parent = 0);

public slots:
    void selectionChanged(void);

protected:
    void keyPressEvent(QKeyEvent *event);

    // Polyline tool
    PolylineDrawingTool poly_tool_;
    RectDrawingTool rect_tool_;
    EllipseDrawingTool ellipse_tool_;

    // Tool callbacks
    void onToolFinished(AToolBase *toolPtr);
};

#endif // SYMBOL_EDITOR_VIEW_H

