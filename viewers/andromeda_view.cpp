#include "andromeda_view.h"
#include "grid/grid.h"

#include <QApplication>
#include <QScrollBar>
#include <QGraphicsItem>
#include <QDebug>

AView::AView(QWidget *parent) : QGraphicsView(parent),
    current_tool_(nullptr),
    cursorStyle_(VIEW_CURSOR_CROSS_SMALL),
    viewFlags_(VIEW_NO_FLAGS),
    mouse_pan_active_(false),
    selection_active_(false)
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
    setScene(new AScene());
}

void AView::setScene(AScene *scene)
{
    scene_ = scene;

    QGraphicsView::setScene(scene);
}

void AView::deleteItems(QList<QGraphicsItem *> items)
{
    if (scene_ == nullptr) return;

    foreach (QGraphicsItem* item, items)
    {
        // NULL ptr
        if (item == nullptr) continue;

        // Item is NOT in the scene
        if (item->scene() != scene_) continue;

        scene_->removeItem(item);
    }

    scene_->update();
}

void AView::deleteSelectedItems()
{
    if (scene_ == nullptr) return;

    deleteItems(scene_->selectedItems());
}

/**
 * @brief AView::setCursorPos
 * Set the position of the cursor (in scene coordinates)
 * @param pos
 */
void AView::setCursorPos(QPointF pos, bool panPastEdges)
{
    double grid = getScene()->getGrid().getMajorTick();

    pos = AGrid::mapToGrid(pos, QPointF(grid,grid));

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

void AView::moveCursor(QPointF offset, bool panPastEdges)
{
    setCursorPos(cursorPos_ + offset, panPastEdges);
}

void AView::moveCursor(double dx, double dy, bool panPastEdges)
{
    moveCursor(QPointF(dx,dy), panPastEdges);
}

/**
 * @brief AView::snapMouseToCursor
 *
 * Move the mouse pointer to the location of the scene cursor
 */
void AView::snapMouseToCursor()
{
    // If the cursorPos is off screen, focus view on that point
    if (!sceneRect().contains(cursorPos_))
    {
        centerOn(cursorPos_);
    }

    QPoint pos = mapToGlobal(mapFromScene(cursorPos_));

    cursor().setPos(pos);
}

void AView::scroll(QPoint offset)
{
    scroll(offset.x(), offset.y());
}

/**
 * @brief AView::scroll
 * Adjust the scroll bar position by a given amount
 * @param dx
 * @param dy
 */
void AView::scroll(int dx, int dy)
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

void AView::keyPressEvent(QKeyEvent *event)
{
    if (event == nullptr) return;

    bool accepted = true;

    double offset = getScene()->getGrid().getMajorTick();

    // First try to send the event to the active tool
    if (isToolActive())
    {
        if (current_tool_->onKeyPress(event))
            return;
    }

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
        cancelTool();
        cancelSelection();
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

void AView::keyReleaseEvent(QKeyEvent *event)
{
    if (isToolActive())
    {
        if (current_tool_->onKeyRelease(event))
        {
            return;
        }
    }
}

/**
 * @brief AView::wheelEvent
 *
 * Called when the mouse wheel is scrolled and this widget has mouse focus
 * @param event
 */
void AView::wheelEvent(QWheelEvent *event)
{
    if (scene_ == NULL || event == nullptr) return;

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

void AView::mousePressEvent(QMouseEvent *event)
{
    if (event == NULL || scene_ == nullptr) return;

    QPointF scenePos = mapToScene(event->pos());

    setCursorPos(scenePos);

    // First try sending the command to the active tool
    if (isToolActive())
    {
        if (current_tool_->onMousePress(event))
        {
            return;
        }
    }

    switch (event->button())
    {
    case Qt::MiddleButton:
        setCursor(QCursor(Qt::OpenHandCursor));
        break;
    case Qt::LeftButton:
        startPos_ = cursorPos_;

        if (!isToolActive())
            startSelection();
        break;

    default:
        break;
    }
}

void AView::mouseDoubleClickEvent(QMouseEvent *event)
{
    if (isToolActive())
    {
        if (current_tool_->onMouseDoubleClick(event))
        {
            return;
        }
    }
}

void AView::mouseReleaseEvent(QMouseEvent *event)
{
    if (scene_ == NULL || event == nullptr) return;

    if (isToolActive())
    {
        if (current_tool_->onMouseRelease(event))
        {
            return;
        }
    }

    // Left mouse button is used for selection
    if (event->button() == Qt::MiddleButton)
    {
        endMousePan();
    }
    else if (event->button() == Qt::LeftButton)
    {
        if (selection_active_)
        {
            finishSelection();
        }
    }
}


void AView::mouseMoveEvent(QMouseEvent *event)
{
    static QPoint lastMousePos;

    if (getScene() == NULL || event == nullptr) return;

    // Grab the mouse position
    QPoint mousePos = event->pos();

    setCursorPos(mapToScene(mousePos));

    if (isToolAvailable())
    {
        if (current_tool_->onMouseMove(event))
        {
            return;
        }
    }

    // Check for panning event
    if (event->buttons() & Qt::MiddleButton)
    {
        if (!mouse_pan_active_)
        {
            startMousePan();
        }
        else
        {
            QPoint delta = mousePos - lastMousePos;
            scroll(delta);
        }

        // Set the panning flag
        lastMousePos = mousePos;
    }
    else
    {
        endMousePan();
    }

    QGraphicsView::mouseMoveEvent(event);
}

void AView::startMousePan()
{
    mouse_pan_active_ = true;
    setCursor(QCursor(Qt::ClosedHandCursor));
}

void AView::endMousePan()
{
    mouse_pan_active_ = false;
    setCursor(QCursor(Qt::ArrowCursor));
}

/*
void AView::drawBackground(QPainter *painter, const QRectF &rect)
{

}
*/

/**
 * @brief AView::drawForeground
 * Custom foreground painting (AFTER the scene is painted)
 * Painting is performed in scene coordinates
 * @param painter
 * @param rect
 */
void AView::drawForeground(QPainter *painter, const QRectF &rect)
{
    if (painter == nullptr) return;

    // Draw the active tool
    if (isToolActive())
    {
        current_tool_->paint(painter, rect);
    }

    else if (selection_active_)
    {
        drawSelectionMarquee(painter, rect);
    }
}

void AView::drawSelectionMarquee(QPainter *painter, const QRectF &rect)
{
    if (painter == nullptr) return;

    QRectF selection = getSelectionMarquee();

    // Don't paint if off-screen
    if (!selection.intersects(rect)) return;

    QPen marqueePen(QColor(0,255,200,200));

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

QRectF AView::getSelectionMarquee()
{
    return QRectF(startPos_.x(),
                  startPos_.y(),
                  cursorPos_.x() - startPos_.x(),
                  cursorPos_.y() - startPos_.y());
}

void AView::paintEvent(QPaintEvent *event)
{
    if (event == nullptr) return;

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

void AView::drawOverlay(QPainter *painter, QRect rect)
{
    // Re-implement this to draw an overlayover the scene

    Q_UNUSED(painter);
    Q_UNUSED(rect);
}

void AView::drawCursor(QPainter *painter, QRect rect)
{
    if (painter == nullptr) return;

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
 * @brief AView::getCenterLocation
 * @return the center of the viewport (in scene coordinates)
 */
QPointF AView::getCenterLocation()
{
    return mapToScene(width()/2,height()/2);
}

/**
 * @brief AView::getViewport
 * @return the viewport rectangle in scene coordinates
 */
QRectF AView::getViewport()
{
    return QRectF(
                mapToScene(0,0),
                mapToScene(width()-verticalScrollBar()->width()-1, height()-horizontalScrollBar()->height()-1)
                );
}

/**
 * @brief AView::unitsPerPixel
 * @return <x,y> mapping of how many internal units correspond to each visible pixel
 */
QPointF AView::unitsPerPixel()
{
    QRectF scene = getViewport();

    return QPointF(scene.width() / width(), scene.height() / height());
}

/**
 * @brief AView::setScalingFactor
 * @param scaling is the desired scaling factor
 */
void AView::setScalingFactor(double scaling)
{
    if (scaling <= 0) return;

    if (scaling > ANDROMEDA_VIEW_MAX_SCALING) scaling = ANDROMEDA_VIEW_MAX_SCALING;
    if (scaling < ANDROMEDA_VIEW_MIN_SCALING) scaling = ANDROMEDA_VIEW_MIN_SCALING;

    // Compensate for the current scaling
    scaling /= getScalingFactor();

    scale(scaling, scaling);
}

/**
 * @brief AView::scaleRelative
 * Scale the view by a specified amount relative to the current scaling
 * @param scaling
 */
void AView::scaleRelative(double scaling)
{
    setScalingFactor(getScalingFactor() * scaling);
}

bool AView::startTool()
{
    return startTool(current_tool_);
}

bool AView::startTool(AToolBase *tool)
{
    if (tool == nullptr)
    {
        return false;
    }

    // Same tool, just keep going
    if (current_tool_ == tool)
    {
        return true;
    }

    // Cancel the current tool
    cancelTool();

    current_tool_ = tool;

    tool->start();

    return true;
}

void AView::cancelTool()
{
    // No tool to cancel
    if (!isToolAvailable())
        return;

    current_tool_->cancel();
}

bool AView::isToolActive()
{
    if (!isToolAvailable())
        return false;

    return current_tool_->isActive();
}

void AView::setViewFlags(unsigned int flags, bool on)
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

void AView::clearViewFlags(unsigned int flags)
{
    setViewFlags(flags, false);
}

bool AView::checkViewFlags(unsigned int flags)
{
    return (viewFlags_ & flags) > 0;
}

void AView::setCursorStyle(unsigned char style)
{
    if (style < VIEW_CURSOR_NUM_STYLES)
    {
        cursorStyle_ = style;
    }
}

void AView::startSelection()
{
    selection_active_ = true;
}

void AView::cancelSelection()
{
    selection_active_ = false;
}

void AView::finishSelection()
{
    if (selection_active_)
    {
        int mods = (int) QApplication::keyboardModifiers();

        QRectF selection = getSelectionMarquee();

        QPointF pixels = unitsPerPixel();

        // Ignore 'small' selections
        bool validSelection = ((qAbs(selection.width()  / pixels.x()) > 5) &&
                               (qAbs(selection.height() / pixels.y()) > 5));

        // Rectangular selection
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


            if (mods & Qt::ControlModifier)
            {
                select = (mods & Qt::ShiftModifier) == 0;
            }
            else
            {
                scene_->clearSelection();
            }

            foreach (QGraphicsItem *item, items)
            {
                if (item == nullptr) continue;

                item->setSelected(select);
            }

            scene_->update();
        }
        // Point Selection
        else
        {
            QGraphicsItem *item = scene_->itemAt(cursorPos_, QTransform());

            // NO item at location, de-select all items
            if (item == nullptr)
            {
                scene_->clearSelection();
            }
            // Toggle selection with control modifier
            else if (mods & Qt::ControlModifier)
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

        cancelSelection();
    }
}
