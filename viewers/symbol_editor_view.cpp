#include "symbol_editor_view.h"

#include "geometry/geometry.h"

#include <QDebug>
#include <QLineF>

#include <QApplication>

SymbolEditorView::SymbolEditorView(QWidget *parent) : AView(parent)
{
    addTool(&poly_tool_);
    addTool(&rect_tool_);
    addTool(&ellipse_tool_);
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
    case Qt::Key_E:
        startTool(&ellipse_tool_);
        break;
    case Qt::Key_R:
        startTool(&rect_tool_);
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


void SymbolEditorView::onToolFinished(AToolBase *toolPtr)
{
    if (toolPtr == nullptr)
        return;

    void *pointer = (void *) toolPtr;

    //TODO - better pointer management, using qobjectcast or similar

    // Pointer comparison fun
    if (pointer == &poly_tool_)
    {
        APolyline *line = new APolyline();

        poly_tool_.getPolyline(*line);

        scene_->addItem(line);

        poly_tool_.reset();
    }
    else if (pointer == &ellipse_tool_)
    {
        AEllipse *ell = new AEllipse();

        ellipse_tool_.getEllipse(*ell);

        if (ell->getRx() > 0 && ell->getRy() > 0)
            scene_->addItem(ell);

        ellipse_tool_.reset();
    }
    else if (pointer == &rect_tool_)
    {
        APolyline *line = new APolyline();

        rect_tool_.getPolyline(*line);

        scene_->addItem(line);

        rect_tool_.reset();
    }
}
