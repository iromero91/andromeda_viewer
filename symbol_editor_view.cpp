#include "symbol_editor_view.h"

SymbolEditorView::SymbolEditorView(QWidget *parent) : AndromedaView(parent)
{
    tmpLine_.setFlag(QGraphicsItem::ItemIsSelectable, false);
    tmpLine_.setFlag(QGraphicsItem::ItemIsFocusable, false);

    tmpLine_.setAcceptHoverEvents(false);
}

void SymbolEditorView::drawForeground(QPainter *painter, const QRectF &rect)
{
    if (checkViewAction(VIEW_ACTION_DRAW_LINE))
    {
        QPen pen(QColor(150,150,150,150));
        pen.setWidth(1);
        pen.setCosmetic(true);
        pen.setStyle(Qt::DashLine);

        painter->setPen(pen);

        if (tmpLine_.points_.count() > 0)
        {
            painter->drawLine(tmpLine_.points_.last().point, cursorPos_);
        }
    }
    AndromedaView::drawForeground(painter,rect);
}

void SymbolEditorView::keyPressEvent(QKeyEvent *event)
{
    if (event == NULL) return;

    bool accepted = true;

    switch (event->key())
    {
    case Qt::Key_Escape:
        cancelLine();
        break;
    default:
        accepted = false;
        break;
    }

    if (!accepted)
    {
        // Pass the event down the chain
        AndromedaView::keyPressEvent(event);
    }
}

void SymbolEditorView::mousePressEvent(QMouseEvent *event)
{
    bool accepted = false;

    if ((event->button() == Qt::LeftButton) && checkViewAction(VIEW_ACTION_DRAW_LINE))
    {
        addLinePoint(cursorPos_);
        accepted = true;
    }


    if (!accepted)
        AndromedaView::mousePressEvent(event);
}

void SymbolEditorView::mouseReleaseEvent(QMouseEvent *event)
{
    AndromedaView::mouseReleaseEvent(event);
}

void SymbolEditorView::mouseMoveEvent(QMouseEvent *event)
{
    AndromedaView::mouseMoveEvent(event);
}

void SymbolEditorView::mouseDoubleClickEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        if (!checkViewAction(VIEW_ACTION_DRAW_LINE))
        {
            setViewAction(VIEW_ACTION_DRAW_LINE);

            startPos_ = cursorPos_;

            startLine(cursorPos_);
        }
        else
        {
            finishLine(cursorPos_);
            clearViewAction(VIEW_ACTION_DRAW_LINE);
        }
    }

    //AndromedaView::mouseDoubleClickEvent(event);
}

void SymbolEditorView::startLine(QPointF pos)
{
    tmpLine_.clear();
    if (tmpLine_.addPoint(pos))
    {
        setViewAction(VIEW_ACTION_DRAW_LINE);
        scene_->addItem(&tmpLine_);
    }
}

void SymbolEditorView::addLinePoint(QPointF pos)
{
    if (!checkViewAction(VIEW_ACTION_DRAW_LINE))
        return;

    tmpLine_.addPoint(pos);

    if (tmpLine_.isClosed())
    {
        addLineToScene();
    }

    scene_->update();
}

void SymbolEditorView::finishLine(QPointF pos)
{
    clearViewAction(VIEW_ACTION_DRAW_LINE);

    tmpLine_.addPoint(pos);

    addLineToScene();

    scene_->update();
}

void SymbolEditorView::addLineToScene()
{
    if (tmpLine_.points_.count() > 1)
    {
        // TODO - This is gross code. But let's copy it across for now
        LWPolyline *line = new LWPolyline();

        foreach (LWPolypoint point, tmpLine_.points_)
        {
            line->addPoint(point);
        }

        lines_.append(line);
        scene_->addItem(line);
    }
    cancelLine();
}

void SymbolEditorView::cancelLine()
{
    clearViewAction(VIEW_ACTION_DRAW_LINE);
    tmpLine_.clear();

    scene_->removeItem(&tmpLine_);
    scene_->update();
}
