#include "symbol_editor_view.h"

#include "geometry.h"

#include "lwpolyline.h"
#include "andromeda_ellipse.h"

#include <QDebug>
#include <QLineF>

#include <QApplication>

SymbolEditorView::SymbolEditorView(QWidget *parent) : AndromedaView(parent)
{
    tmpLine_.setFlag(QGraphicsItem::ItemIsSelectable, false);
    tmpLine_.setFlag(QGraphicsItem::ItemIsFocusable, false);
    tmpLine_.setAcceptHoverEvents(false);
    tmpLine_.setVisible(false);

    scene_->addItem(&tmpLine_);

    tmpEllipse_.setFlag(QGraphicsItem::ItemIsSelectable, false);
    tmpEllipse_.setFlag(QGraphicsItem::ItemIsFocusable, false);
    tmpEllipse_.setAcceptHoverEvents(false);
    tmpEllipse_.setVisible(false);

    scene_->addItem(&tmpEllipse_);
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
    case VIEW_ACTION_LINE_ADD_POINT:
        if (tmpLine_.points_.count() > 0)
        {
            painter->drawLine(tmpLine_.points_.last().point, cursorPos_);
        }
        break;
    case VIEW_ACTION_ELLIPSE_SET_RADIUS:
        painter->drawLine(tmpEllipse_.pos(), cursorPos_);
        break;
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
    case Qt::Key_X: // Delete
        deleteSelectedItems();
        break;
    case Qt::Key_Escape:
        popAction();
        break;
    case Qt::Key_E:
        ellipseMode();
        break;
    case Qt::Key_L:
        lineMode();
        break;
    case Qt::Key_R:
        rectMode();
        break;
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

    setCursorPos(mapToScene(event->pos()));

    if ((event->button() == Qt::LeftButton))
    {
        switch (getAction())
        {
        case VIEW_ACTION_LINE_SET_START:
            popAction();
            pushAction(VIEW_ACTION_LINE_ADD_POINT);
            startLine(cursorPos_);
            break;
        case VIEW_ACTION_LINE_ADD_POINT:
            addLinePoint(cursorPos_);
            break;

        case VIEW_ACTION_ELLIPSE_SET_CENTER:
            startPos_ = cursorPos_;

            popAction();
            pushAction(VIEW_ACTION_ELLIPSE_SET_RADIUS);

            tmpEllipse_.setVisible(true);
            setEllipseCenter(startPos_);

            break;

        case VIEW_ACTION_ELLIPSE_SET_RADIUS:
            popAction();
            addEllipseToScene();
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

    QPointF pos = mapToScene(event->pos());

    switch (getAction())
    {
    case VIEW_ACTION_ELLIPSE_SET_RADIUS:
        setEllipseRadius(cursorPos_);
        break;
    }

}

void SymbolEditorView::mouseDoubleClickEvent(QMouseEvent *event)
{
    unsigned int action = getAction();

    if (event->button() == Qt::LeftButton)
    {
        switch (action)
        {
        case VIEW_ACTION_LINE_SET_START:
        case VIEW_ACTION_LINE_ADD_POINT:
            finishLine(cursorPos_);
            break;

        default:
            break;
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
    switch (action)
    {
    case VIEW_ACTION_ELLIPSE_SET_CENTER:
    case VIEW_ACTION_ELLIPSE_SET_RADIUS:
        tmpEllipse_.setVisible(false);
        break;
    case VIEW_ACTION_LINE_SET_START:
    case VIEW_ACTION_LINE_ADD_POINT:
        tmpLine_.setVisible(false);
        break;
    }
}

void SymbolEditorView::lineMode()
{
    switch (getAction())
    {
    case VIEW_ACTION_LINE_ADD_POINT:
    case VIEW_ACTION_LINE_SET_START:
        return;
    }

    clearActions();
    pushAction(VIEW_ACTION_LINE_SET_START);
}

void SymbolEditorView::rectMode()
{
    switch (getAction())
    {
    case VIEW_ACTION_RECT_SET_START:
    case VIEW_ACTION_RECT_SET_CORNER:
        return;
    }

    clearActions();
    pushAction(VIEW_ACTION_RECT_SET_START);
}

void SymbolEditorView::startLine(QPointF pos)
{
    tmpLine_.clear();
    if (tmpLine_.addPoint(pos))
    {
        tmpLine_.setVisible(true);
    }
}

void SymbolEditorView::addLinePoint(QPointF pos)
{
    if (getAction() != VIEW_ACTION_LINE_ADD_POINT)
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

        scene_->addItem(line);
    }
}

void SymbolEditorView::ellipseMode()
{
    switch (getAction())
    {
    case VIEW_ACTION_ELLIPSE_SET_CENTER:
    case VIEW_ACTION_ELLIPSE_SET_RADIUS:
        return;
    }

    clearActions();
    pushAction(VIEW_ACTION_ELLIPSE_SET_CENTER);
}

void SymbolEditorView::setEllipseCenter(QPointF point)
{
    tmpEllipse_.setPos(point);
    tmpEllipse_.setRadius(0,0);
}

void SymbolEditorView::setEllipseRadius(QPointF point)
{
    QPointF delta = point - tmpEllipse_.pos();

    double rx = fabs(delta.x());
    double ry = fabs(delta.y());

    if (QApplication::keyboardModifiers() == Qt::ControlModifier)
    {
        rx = qMax(rx, ry);
        ry = rx;
    }

    tmpEllipse_.setRadius(rx,ry);
    tmpEllipse_.update();
}

void SymbolEditorView::addEllipseToScene()
{
    if ((tmpEllipse_.getRx() > 0) && (tmpEllipse_.getRy() > 0))
    {
        AndromedaEllipse *ellipse = new AndromedaEllipse();

        ellipse->setPos(tmpEllipse_.pos());

        ellipse->setRadius(tmpEllipse_.getRx(), tmpEllipse_.getRy());

        scene_->addItem(ellipse);
    }

    tmpEllipse_.setVisible(false);
}
