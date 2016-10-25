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
    void keyPressEvent(QKeyEvent *event);

    // Polyline tool
    PolylineDrawingTool poly_tool_;

    // Tool callbacks
    void onToolFinished(QObject *toolPtr);
};

#endif // SYMBOL_EDITOR_VIEW_H

