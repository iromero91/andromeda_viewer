#include "symbol_editor_view.h"

#include "geometry/geometry.h"

#include <QDebug>
#include <QLineF>

#include <QApplication>

SymbolEditorView::SymbolEditorView(QWidget *parent) : AView(parent)
{
    addTool(&poly_tool_);
}

void SymbolEditorView::keyPressEvent(QKeyEvent *event)
{
    if (event == nullptr) return;

    bool accepted = true;

    switch (event->key())
    {
    case Qt::Key_X: // Delete
        deleteSelectedItems();
        break;
    case Qt::Key_L:
        startTool(&poly_tool_);
        break;
    default:
        accepted = false;
        break;
    }

    // If not used, pass upstream
    if (!accepted)
    {
        // Pass the event down the chain
        AView::keyPressEvent(event);
    }

    update();
}


void SymbolEditorView::onToolFinished(QObject *toolPtr)
{
    int pointer = (int) toolPtr;

    // Pointer comparison fun
    if (pointer == (int) &poly_tool_)
    {
        APolyline *line = new APolyline();

        poly_tool_.getPolyline(*line);

        scene_->addItem(line);

        poly_tool_.reset();
    }
}
