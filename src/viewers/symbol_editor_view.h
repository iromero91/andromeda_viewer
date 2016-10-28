#ifndef SYMBOL_EDITOR_VIEW_H
#define SYMBOL_EDITOR_VIEW_H

#include "src/shapes/polyline.h"
#include "src/shapes/ellipse.h"

#include "src/tools/polyline_drawing_tool.h"
#include "src/tools/ellipse_drawing_tool.h"
#include "src/tools/rect_drawing_tool.h"

#include "andromeda_view.h"

class SymbolEditorView : public AView
{
    Q_OBJECT

public:
    SymbolEditorView(QWidget * parent = 0);

public slots:
    //TODO these are just hacky. To be remove
    void drawRect(void)     { startTool(&rect_tool_); }
    void drawEllipse(void)  { startTool(&ellipse_tool_); }
    void drawPolyline(void) { startTool(&poly_tool_); }

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

