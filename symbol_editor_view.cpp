#include "symbol_editor_view.h"

#include "geometry.h"

#include <QDebug>
#include <QLineF>

SymbolEditorView::SymbolEditorView(QWidget *parent) : AndromedaView(parent)
{
    tmpLine_.setFlag(QGraphicsItem::ItemIsSelectable, false);
    tmpLine_.setFlag(QGraphicsItem::ItemIsFocusable, false);

    tmpLine_.setAcceptHoverEvents(false);
}

void SymbolEditorView::drawForeground(QPainter *painter, const QRectF &rect)
{
    QPen pen(QColor(150,150,150,150));
    pen.setWidth(1);
    pen.setCosmetic(true);
    pen.setStyle(Qt::DashLine);

    painter->setPen(pen);

    switch (getAction())
    {
    case VIEW_ACTION_DRAW_LINE:
        if (tmpLine_.points_.count() > 0)
        {
            painter->drawLine(tmpLine_.points_.last().point, cursorPos_);
        }
        break;
    case VIEW_ACTION_ADD_CURVE:
        if (tmpLine_.points_.count() > 1)
        {

            QPointF p1 = tmpLine_.points_.at(tmpLine_.points_.count()-2).point;
            QPointF p2 = tmpLine_.points_.last().point;

            QLineF line(p1, p2);

            QPointF mid = Midpoint(p1, p2);

            painter->drawLine(tmpLine_.points_.last().point, cursorPos_);
            painter->drawLine(tmpLine_.points_.at(tmpLine_.points_.count()-2).point, cursorPos_);
        }
    default:
        break;
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
    bool accepted = true;

    if ((event->button() == Qt::LeftButton))
    {
        switch (getAction())
        {
        case VIEW_ACTION_DRAW_LINE:
            addLinePoint(cursorPos_);
            accepted = true;

            if (event->modifiers() == Qt::AltModifier)
            {
                if (tmpLine_.points_.count() > 1)
                {
                    pushAction(VIEW_ACTION_ADD_CURVE);
                }
            }

            break;
        case VIEW_ACTION_ADD_CURVE:
            //TODO
            break;
        default:
            accepted = false;
            break;
        }
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
    unsigned int action = getAction();

    if (event->button() == Qt::LeftButton)
    {

        if (action != VIEW_ACTION_DRAW_LINE)
        {
            startLine(cursorPos_);
        }
        else
        {
            finishLine(cursorPos_);
            popAction();
        }
    }

    //AndromedaView::mouseDoubleClickEvent(event);
}

void SymbolEditorView::onActionAdded(unsigned int action)
{
    //TODO
}

void SymbolEditorView::onActionCancelled(unsigned int action)
{
    //TODO
}

void SymbolEditorView::startLine(QPointF pos)
{
    tmpLine_.clear();
    if (tmpLine_.addPoint(pos))
    {
        pushAction(VIEW_ACTION_DRAW_LINE);
        scene_->addItem(&tmpLine_);
    }
}

void SymbolEditorView::addLinePoint(QPointF pos)
{
    if (getAction() != VIEW_ACTION_DRAW_LINE)
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
    popAction();

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
    popAction(VIEW_ACTION_DRAW_LINE);
    tmpLine_.clear();

    scene_->removeItem(&tmpLine_);
    scene_->update();
}
