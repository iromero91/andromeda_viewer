#include "symbol_editor_view.h"

#include "geometry/geometry.h"

#include <QDebug>
#include <QLineF>

#include <QApplication>

SymbolEditorView::SymbolEditorView(QWidget *parent) : AView(parent)
{
}

void SymbolEditorView::drawForeground(QPainter *painter, const QRectF &rect)
{
    QPen pen(QColor(150,150,150,150));
    pen.setWidth(1);
    pen.setCosmetic(true);
    pen.setStyle(Qt::DashLine);

    //painter->setPen(pen);

    AView::drawForeground(painter,rect);
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

void SymbolEditorView::keyReleaseEvent(QKeyEvent *event)
{
    bool accepted = false;

    if (!accepted)
    {
        AView::keyReleaseEvent(event);
    }
}

void SymbolEditorView::mousePressEvent(QMouseEvent *event)
{
    bool accepted = false;

    setCursorPos(mapToScene(event->pos()));

    startPos_ = cursor_pos_;

    if (!accepted)
        AView::mousePressEvent(event);
}

void SymbolEditorView::mouseReleaseEvent(QMouseEvent *event)
{
    AView::mouseReleaseEvent(event);
}

void SymbolEditorView::mouseMoveEvent(QMouseEvent *event)
{
    AView::mouseMoveEvent(event);
}

void SymbolEditorView::mouseDoubleClickEvent(QMouseEvent *event)
{
    AView::mouseDoubleClickEvent(event);
}
