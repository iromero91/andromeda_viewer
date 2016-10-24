#include "symbol_editor_view.h"

#include "geometry/geometry.h"

#include <QDebug>
#include <QLineF>

#include <QApplication>

SymbolEditorView::SymbolEditorView(QWidget *parent) : AView(parent)
{
    addTempItem(&tmpLine_);
    addTempItem(&tmpEllipse_);
    addTempItem(&tmpRect_);

    scene_->addItem(&poly_tool_);
}

void SymbolEditorView::addTempItem(QGraphicsItem *item)
{
    if (item == NULL) return;

    item->setFlag(QGraphicsItem::ItemIsSelectable, false);
    item->setFlag(QGraphicsItem::ItemIsFocusable, false);
    item->setAcceptHoverEvents(false);
    item->setVisible(false);
    item->setZValue(INT_MAX);

    if (scene_ != NULL)
        scene_->addItem(item);
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
    case VIEW_ACTION_RECT_SET_FINISH:
        updateRect(cursorPos_);
        painter->drawLine(startPos_, cursorPos_);
        break;
    case VIEW_ACTION_ELLIPSE_SET_RADIUS:
        setEllipseRadius(cursorPos_);
        painter->drawLine(tmpEllipse_.pos(), cursorPos_);
        break;
    default:
        break;
    }

    AView::drawForeground(painter,rect);
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
    case Qt::Key_F:
        //TODO - toggle shape fill
        break;
    case Qt::Key_L:
        lineMode();
        break;
    case Qt::Key_R:
        rectMode();
        break;
    default:
        accepted = false;
        break;
    }

    if (!accepted)
    {
        // Pass the event down the chain
        AView::keyPressEvent(event);
    }

    update();
}

void SymbolEditorView::keyReleaseEvent(QKeyEvent *event)
{
    update();
}

void SymbolEditorView::mousePressEvent(QMouseEvent *event)
{
    bool accepted = true;

    setCursorPos(mapToScene(event->pos()));

    startPos_ = cursorPos_;

    if ((event->button() == Qt::LeftButton))
    {
        switch (getAction())
        {

        // Line functions
        case VIEW_ACTION_LINE_SET_START:
            popAction();
            pushAction(VIEW_ACTION_LINE_ADD_POINT);
            startLine(cursorPos_);
            break;
        case VIEW_ACTION_LINE_ADD_POINT:
            addLinePoint(cursorPos_);
            break;

        // Ellipse functions
        case VIEW_ACTION_ELLIPSE_SET_CENTER:

            popAction();
            pushAction(VIEW_ACTION_ELLIPSE_SET_RADIUS);

            setEllipseCenter(startPos_);
            tmpEllipse_.setVisible(true);

            break;
        case VIEW_ACTION_ELLIPSE_SET_RADIUS:
            popAction();
            addEllipse();
            break;

        // Rect functions
        case VIEW_ACTION_RECT_SET_START:
            startRect(cursorPos_);
            tmpRect_.setVisible(true);
            break;
        case VIEW_ACTION_RECT_SET_FINISH:
            addRect();
            popAction();
            break;

        default:
            accepted = false;
            break;
        }
    }


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

    switch (getAction())
    {
    case VIEW_ACTION_ELLIPSE_SET_RADIUS:
        setEllipseRadius(cursorPos_);
        break;
    case VIEW_ACTION_RECT_SET_FINISH:
        updateRect(cursorPos_);
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

    //AView::mouseDoubleClickEvent(event);
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
    case VIEW_ACTION_RECT_SET_FINISH:
    case VIEW_ACTION_RECT_SET_START:
        tmpRect_.setVisible(false);
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

    //TODO - Check for self-overlapping intersections

    tmpLine_.addPoint(pos);

    if (tmpLine_.isClosed())
    {
        addLine();
    }

    scene_->update();
}

void SymbolEditorView::finishLine(QPointF pos)
{
    popAction();

    tmpLine_.addPoint(pos);

    addLine();

    scene_->update();
}

void SymbolEditorView::addLine()
{
    if (tmpLine_.points_.count() > 1)
    {
        // TODO - This is gross code. But let's copy it across for now
        APolyline *line = new APolyline();

        foreach (LWPolypoint point, tmpLine_.points_)
        {
            line->addPoint(point);
        }

        scene_->addItem(line);
    }

    clearActions();

    tmpLine_.setVisible(false);
}

void SymbolEditorView::rectMode()
{
    switch (getAction())
    {
    case VIEW_ACTION_RECT_SET_START:
    case VIEW_ACTION_RECT_SET_FINISH:
        return;
    }

    clearActions();
    pushAction(VIEW_ACTION_RECT_SET_START);
}

void SymbolEditorView::startRect(QPointF pos, double width, double height)
{

    tmpRect_.setPos(pos);
    tmpRect_.setSize(0,0);
    tmpRect_.setVisible(true);

    popAction(VIEW_ACTION_RECT_SET_START);
    pushAction(VIEW_ACTION_RECT_SET_FINISH);
}

void SymbolEditorView::updateRect(QPointF pos)
{
    QPointF delta = pos - startPos_;

    double x = delta.x();
    double y = delta.y();

    if (QApplication::keyboardModifiers() & Qt::ControlModifier)
    {
        x = qMax(x,y);
        y = x;
    }

    // SHIFT key draws the rectangle centered at the first point
    if (QApplication::keyboardModifiers() & Qt::ShiftModifier)
    {
        tmpRect_.setPos(startPos_ - QPointF(x,y));
        x *= 2;
        y *= 2;

    }
    else
    {
        tmpRect_.setPos(startPos_);
    }

    tmpRect_.setSize(x,y);
}

void SymbolEditorView::addRect()
{
    clearActions();

    QRectF rect = tmpRect_.getRect().normalized();

    if (rect.width() == 0 || rect.height() == 0)
        return;

    rect.translate(tmpRect_.pos());

    tmpRect_.setVisible(false);

    APolyline *line = new APolyline();

    // Convert the rectangle into a polyline
    line->addPoint(rect.topLeft());
    line->addPoint(rect.topRight());
    line->addPoint(rect.bottomRight());
    line->addPoint(rect.bottomLeft());
    line->addPoint(rect.topLeft());

    scene_->addItem(line);
}


void SymbolEditorView::addRect(QPointF pStart, QPointF pEnd)
{
    //TODO
}

void SymbolEditorView::addRect(QPointF pStart, double width, double height)
{
    addRect(pStart, QPointF(pStart.x() + width, pStart.y() + height));
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

/**
 * @brief SymbolEditorView::addEllipse
 * Make a copy of the temporary ellipse and add it to the scene
 */
void SymbolEditorView::addEllipse()
{
    if ((tmpEllipse_.getRx() > 0) && (tmpEllipse_.getRy() > 0))
    {
        AEllipse *ellipse = new AEllipse();

        ellipse->setPos(tmpEllipse_.pos());

        ellipse->setRadius(tmpEllipse_.getRx(), tmpEllipse_.getRy());

        scene_->addItem(ellipse);
    }

    tmpEllipse_.setVisible(false);
}

void SymbolEditorView::addEllipse(QPointF center, double rx, double ry)
{
    if (scene_ == NULL) return;

    AEllipse *e = new AEllipse();

    e->setPos(center);
    e->setRadius(rx, ry);

    scene_->addItem(e);
}

void SymbolEditorView::addEllipse(QPointF center, double radius)
{
    addEllipse(center, radius, radius);
}
