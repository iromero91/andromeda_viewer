#include "andromeda_view.h"
#include "andromeda_grid.h"

#include <QScrollBar>
#include <QGraphicsItem>
#include <QDebug>

AndromedaView::AndromedaView(QWidget *parent) :
    QGraphicsView(parent),
    cursorStyle_(VIEW_CURSOR_CROSS_SMALL),
    viewFlags_(VIEW_NO_FLAGS)
{
    setMouseTracking(true);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOn);

    setRenderHint(QPainter::Antialiasing);
    setRenderHint(QPainter::HighQualityAntialiasing);
    setRenderHint(QPainter::TextAntialiasing);

    setDragMode(QGraphicsView::RubberBandDrag);
    setViewportUpdateMode(QGraphicsView::FullViewportUpdate);

    // Add a default scene
    setScene(new AndromedaScene());
}

void AndromedaView::setScene(AndromedaScene *scene)
{
    scene_ = scene;

    QGraphicsView::setScene(scene);
}

void AndromedaView::deleteItems(QList<QGraphicsItem *> items)
{
    if (scene_ == NULL) return;

    foreach (QGraphicsItem* item, items)
    {
        // NULL ptr
        if (item == NULL) continue;

        // Item is NOT in the scene
        if (item->scene() != scene_) continue;

        scene_->removeItem(item);
    }

    scene_->update();
}

void AndromedaView::deleteSelectedItems()
{
    if (scene_ == NULL) return;

    deleteItems(scene_->selectedItems());
}

/**
 * @brief AndromedaView::setCursorPos
 * Set the position of the cursor (in scene coordinates)
 * @param pos
 */
void AndromedaView::setCursorPos(QPointF pos, bool panPastEdges)
{
    double grid = getScene()->getGrid().getMajorTick();

    pos = AndromedaGrid::mapToGrid(pos, QPointF(grid,grid));

    if ((pos.x() == cursorPos_.x()) && (pos.y() == cursorPos_.y())) return;

    if (panPastEdges)
    {
        // Check if the cursor has moved outside the screen bounds
        QRectF view = getViewport();

        double dx = 0;
        double dy = 0;

        if (pos.x() < view.left())
            dx = view.left() - pos.x();
        else if (pos.x() > view.right())
            dx = view.right() - pos.x();

        if (pos.y() < view.top())
            dy = view.top() - pos.y();
        else if (pos.y() > view.bottom())
            dy = view.bottom() - pos.y();

        scroll(dx,dy);
    }

    cursorPos_ = pos;

    emit cursorPositionChanged(cursorPos_);

    getScene()->update();
}

void AndromedaView::moveCursor(QPointF offset, bool panPastEdges)
{
    setCursorPos(cursorPos_ + offset, panPastEdges);
}

void AndromedaView::moveCursor(double dx, double dy, bool panPastEdges)
{
    moveCursor(QPointF(dx,dy), panPastEdges);
}

/**
 * @brief AndromedaView::snapMouseToCursor
 *
 * Move the mouse pointer to the location of the scene cursor
 */
void AndromedaView::snapMouseToCursor()
{
    // If the cursorPos is off screen, focus view on that point
    if (!sceneRect().contains(cursorPos_))
    {
        centerOn(cursorPos_);
    }

    QPoint pos = mapToGlobal(mapFromScene(cursorPos_));

    cursor().setPos(pos);
}

void AndromedaView::scroll(QPoint offset)
{
    scroll(offset.x(), offset.y());
}

/**
 * @brief AndromedaView::scroll
 * Adjust the scroll bar position by a given amount
 * @param dx
 * @param dy
 */
void AndromedaView::scroll(int dx, int dy)
{
    bool update = false;

    if (dx != 0)
    {
        update = true;
        horizontalScrollBar()->setValue(horizontalScrollBar()->value() - dx);
    }
    if (dy != 0)
    {
        update = true;
        verticalScrollBar()->setValue(verticalScrollBar()->value() - dy);
    }

    if (update)
        scene()->update();


}

void AndromedaView::keyPressEvent(QKeyEvent *event)
{
    if (event == NULL) return;

    bool accepted = true;

    double offset = getScene()->getGrid().getMajorTick();

    switch (event->key())
    {
    case Qt::Key_Space:
        // Center the screen at the cursor location
        if (event->modifiers() == Qt::ControlModifier)
        {
            centerOn(cursorPos_);
        }
        // Reset the cursor origin to the current cursor position
        else
        {
            cursorOrigin_ = cursorPos_;
            emit cursorPositionChanged(cursorPos_);
        }
        snapMouseToCursor();
        break;
    // Move the cursor left
    case Qt::Key_Left:
        moveCursor(-offset,0,true);
        snapMouseToCursor();
        break;
    // Move the cursor right
    case Qt::Key_Right:
        moveCursor(offset,0,true);
        snapMouseToCursor();
        break;
    // Move the cursor up
    case Qt::Key_Up:
        moveCursor(0,-offset,true);
        snapMouseToCursor();
        break;
    // Move the cursor down
    case Qt::Key_Down:
        moveCursor(0,offset,true);
        snapMouseToCursor();
        break;
    // Cancel the current action
    case Qt::Key_Escape:
        popAction();
        scene_->update();
        break;

    case Qt::Key_C: //TODO - remove this, just a test
        setCursorStyle(getCursorStyle() == VIEW_CURSOR_CROSS_LARGE ? VIEW_CURSOR_CROSS_SMALL : VIEW_CURSOR_CROSS_LARGE);
        scene_->update();
        break;

    default:
        accepted = false;
        break;
    }

    if (accepted)
    {
        event->accept();
    }
    else
    {
        QGraphicsView::keyPressEvent(event);
    }
}

/**
 * @brief AndromedaView::wheelEvent
 *
 * Called when the mouse wheel is scrolled and this widget has mouse focus
 * @param event
 */
void AndromedaView::wheelEvent(QWheelEvent *event)
{
    if (scene_ == NULL || event == NULL) return;

    float zoom = (float) event->delta() * 0.01f;

    // Account for 'negative' zoom
    if (zoom < 0)
        zoom = -1.0 / zoom;

    scaleRelative(zoom);

    // Re-move the cursor to the mouse position
    QPoint mousePos = mapFromGlobal(cursor().pos());

    setCursorPos(mapToScene(mousePos));

    //event->accept();
}

void AndromedaView::mousePressEvent(QMouseEvent *event)
{
    if (event == NULL || scene_ == NULL) return;

    QPointF scenePos = mapToScene(event->pos());

    setCursorPos(scenePos);

    // Selection
    if (event->button() == Qt::LeftButton)
    {
        startPos_ = cursorPos_;

        pushAction(VIEW_ACTION_SELECTING);
    }
}



void AndromedaView::mouseDoubleClickEvent(QMouseEvent *event)
{
}

void AndromedaView::mouseReleaseEvent(QMouseEvent *event)
{
    if (scene_ == NULL || event == NULL) return;

    // Left mouse button is used for selection
    if (event->button() == Qt::LeftButton)
    {
        QPointF pixels = unitsPerPixel();
        QRectF selection = getSelectionMarquee();

        unsigned int action = getAction();

        if (action == VIEW_ACTION_SELECTING)
        {

            // Finished selecting
            popAction();

            // Ignore 'small' selections
            bool validSelection = ((qAbs(selection.width()  / pixels.x()) > 5) &&
                                   (qAbs(selection.height() / pixels.y()) > 5));



            if (validSelection)
            {

                QList<QGraphicsItem*> items;

                // Selection drawn left-to-right requires full selection
                if (selection.width() > 0)
                {
                    items = scene_->items(selection, Qt::ContainsItemShape);
                }
                else
                {
                    items = scene_->items(selection.normalized(), Qt::IntersectsItemShape);
                }

                bool select = true;

                if (event->modifiers() & Qt::ControlModifier)
                {
                    select = (event->modifiers() & Qt::ShiftModifier) == 0;
                }
                else
                {
                    scene_->clearSelection();
                }

                foreach (QGraphicsItem *item, items)
                {
                    if (item == NULL) continue;

                    item->setSelected(select);
                }

                scene_->update();
            }
            else
            {
                QGraphicsItem *item = scene_->itemAt(cursorPos_, QTransform());

                // NO item at location, de-select all items
                if (item == NULL)
                {
                    scene_->clearSelection();
                }
                // Toggle selection with control modifier
                else if (event->modifiers() & Qt::ControlModifier)
                {
                    item->setSelected(!item->isSelected());
                }
                // Otherwise, clear selection and select this one item
                else
                {
                    scene_->clearSelection();
                    item->setSelected(true);
                }

                scene_->update();
            }
        }
    }
}


void AndromedaView::mouseMoveEvent(QMouseEvent *event)
{
    static bool panning = false;
    static QPoint lastMousePos;

    if (getScene() == NULL || event == NULL) return;

    // Grab the mouse position
    QPoint mousePos = event->pos();

    setCursorPos(mapToScene(mousePos));

    // Check for panning event
    if (event->buttons() & Qt::MiddleButton)
    {

        if (panning)
        {
            QPoint delta = mousePos - lastMousePos;

            scroll(delta);
        }

        // Set the panning flag
        panning = true;
        lastMousePos = mousePos;
    }
    else
    {
        panning = false;
    }

    QGraphicsView::mouseMoveEvent(event);
}

/*
void AndromedaView::drawBackground(QPainter *painter, const QRectF &rect)
{

}
*/

/**
 * @brief AndromedaView::drawForeground
 * Custom foreground painting (AFTER the scene is painted)
 * Painting is performed in scene coordinates
 * @param painter
 * @param rect
 */
void AndromedaView::drawForeground(QPainter *painter, const QRectF &rect)
{
    if (painter == NULL) return;

    if (getAction() == VIEW_ACTION_SELECTING)
    {
        drawSelectionMarquee(painter, rect);
    }
}

void AndromedaView::drawSelectionMarquee(QPainter *painter, const QRectF &rect)
{
    QPen marqueePen(QColor(0,255,200,200));

    QRectF selection = getSelectionMarquee();
    bool crossing = selection.width() < 0;

    marqueePen.setCapStyle(Qt::RoundCap);
    marqueePen.setJoinStyle(Qt::RoundJoin);
    marqueePen.setWidth(1);
    marqueePen.setStyle(crossing ? Qt::DashLine : Qt::SolidLine);

    marqueePen.setCosmetic(true);

    QBrush marqueeBrush(crossing? QColor(0,120,50,50) : QColor(0,50,120,50));

    painter->setPen(marqueePen);
    painter->setBrush(marqueeBrush);

    painter->drawRect(selection.normalized());
}

QRectF AndromedaView::getSelectionMarquee()
{
    return QRectF(startPos_.x(),
                  startPos_.y(),
                  cursorPos_.x() - startPos_.x(),
                  cursorPos_.y() - startPos_.y());
}

void AndromedaView::paintEvent(QPaintEvent *event)
{
    if (event == NULL) return;

    // First perform scene painting
    QGraphicsView::paintEvent(event);

    // Grab the painter
    QPainter painter(viewport());

    // Draw the cursor
    drawCursor(&painter, event->rect());

    // Draw the overlay
    if (checkViewFlags(VIEW_FLAG_DRAW_OVERLAY))
        drawOverlay(&painter, event->rect());
}

void AndromedaView::drawOverlay(QPainter *painter, QRect rect)
{
    // Re-implement this to draw an overlayover the scene
}

void AndromedaView::drawCursor(QPainter *painter, QRect rect)
{
    if (painter == NULL) return;

    QPoint viewPos = mapFromScene(cursorPos_);
    int x = viewPos.x();
    int y = viewPos.y();

    QPen p;
    p.setWidth(1);

    painter->setPen(p);

    switch (cursorStyle_)
    {
    default:
    case VIEW_CURSOR_NONE:
        return;

    // Draw a small cross at the cursor position
    case VIEW_CURSOR_CROSS_SMALL:
#define CURSOR 10
        // Is the cursor position in view?
        if ((viewPos.x() > -CURSOR) &&
            (viewPos.x() < (width() + CURSOR)) &&
            (viewPos.y() > -CURSOR) &&
            (viewPos.y() < (height() + CURSOR)))
        {
            painter->drawLine(x-CURSOR,y,x+CURSOR,y);
            painter->drawLine(x,y-CURSOR,x,y+CURSOR);
        }
        break;

    case VIEW_CURSOR_CROSS_LARGE:

        // Draw horizontal line
        painter->drawLine(rect.left() - 1,
                          y,
                          rect.right() + 1,
                          y);

        // Draw vertical line
        painter->drawLine(x,
                          rect.top() - 1,
                          x,
                          rect.bottom() + 1);

        break;
    }
}

/**
 * @brief AndromedaView::getCenterLocation
 * @return the center of the viewport (in scene coordinates)
 */
QPointF AndromedaView::getCenterLocation()
{
    return mapToScene(width()/2,height()/2);
}

/**
 * @brief AndromedaView::getViewport
 * @return the viewport rectangle in scene coordinates
 */
QRectF AndromedaView::getViewport()
{
    return QRectF(
                mapToScene(0,0),
                mapToScene(width()-verticalScrollBar()->width()-1, height()-horizontalScrollBar()->height()-1)
                );
}

/**
 * @brief AndromedaView::unitsPerPixel
 * @return <x,y> mapping of how many internal units correspond to each visible pixel
 */
QPointF AndromedaView::unitsPerPixel()
{
    QRectF scene = getViewport();

    return QPointF(scene.width() / width(), scene.height() / height());
}

/**
 * @brief AndromedaView::setScalingFactor
 * @param scaling is the desired scaling factor
 */
void AndromedaView::setScalingFactor(double scaling)
{
    if (scaling <= 0) return;

    if (scaling > ANDROMEDA_VIEW_MAX_SCALING) scaling = ANDROMEDA_VIEW_MAX_SCALING;
    if (scaling < ANDROMEDA_VIEW_MIN_SCALING) scaling = ANDROMEDA_VIEW_MIN_SCALING;

    // Compensate for the current scaling
    scaling /= getScalingFactor();

    scale(scaling, scaling);
}

/**
 * @brief AndromedaView::scaleRelative
 * Scale the view by a specified amount relative to the current scaling
 * @param scaling
 */
void AndromedaView::scaleRelative(double scaling)
{
    setScalingFactor(getScalingFactor() * scaling);
}

unsigned int AndromedaView::getAction()
{
    if (actionStack_.count() > 0)
    {
        return actionStack_.last();
    }

    return (unsigned int) VIEW_NO_ACTION;
}

bool AndromedaView::pushAction(unsigned int action, bool allowDuplicates)
{
    if (!allowDuplicates && (action == getAction()))
        return false;

    actionStack_.append(action);

    onActionAdded(action);

    emit actionAdded(action);

    return true;
}

bool AndromedaView::popAction()
{
    if (actionStack_.count() > 0)
    {
        unsigned int action = actionStack_.last();

        actionStack_.removeLast();

        onActionCancelled(action);

        emit actionCancelled(action);

        return true;
    }

    return false;
}

bool AndromedaView::popAction(unsigned int action)
{
    if (getAction() == action)
    {
        return popAction();
    }

    return false;
}

void AndromedaView::clearActions()
{
    while (actionStack_.count() > 0)
        popAction();
}

void AndromedaView::setViewFlags(unsigned int flags, bool on)
{
    if (on)
    {
        viewFlags_ |= flags;
    }
    else
    {
        viewFlags_ &= ~flags;
    }
}

void AndromedaView::clearViewFlags(unsigned int flags)
{
    setViewFlags(flags, false);
}

bool AndromedaView::checkViewFlags(unsigned int flags)
{
    return (viewFlags_ & flags) > 0;
}

void AndromedaView::setCursorStyle(unsigned char style)
{
    if (style < VIEW_CURSOR_NUM_STYLES)
    {
        cursorStyle_ = style;
    }
}
