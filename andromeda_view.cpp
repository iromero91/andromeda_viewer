#include "andromeda_view.h"
#include "andromeda_grid.h"

#include <QScrollBar>
#include <QGraphicsItem>
#include <QDebug>

AndromedaView::AndromedaView(QWidget *parent) :
    QGraphicsView(parent),
    viewAction_(VIEW_NO_ACTION),
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
    setViewportUpdateMode(QGraphicsView::SmartViewportUpdate);

    // Add a default scene
    setScene(new AndromedaScene());
}

void AndromedaView::setScene(AndromedaScene *scene)
{
    scene_ = scene;

    QGraphicsView::setScene(scene);
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
        cancelViewAction();
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

    event->accept();
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

        setViewAction(VIEW_ACTION_SELECTING);
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

        // Ignore 'small' selections
        bool validSelection = (checkViewAction(VIEW_ACTION_SELECTING)) &&
                              (qAbs(selection.width() / pixels.x()) > 5) &&
                              (qAbs(selection.height() / pixels.y()) > 5);


        clearViewAction(VIEW_ACTION_SELECTING);

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
                items = scene_->items(selection, Qt::IntersectsItemShape);
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

    if (event->buttons() & Qt::LeftButton)
    {

    }
    else
    {
        clearViewAction(VIEW_ACTION_SELECTING);
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

    if (checkViewAction(VIEW_ACTION_SELECTING))
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
    // Only returns valid selection rect if currently selecting
    if (!checkViewAction(VIEW_ACTION_SELECTING))
        return QRectF();

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

void AndromedaView::setViewAction(unsigned int action, bool on)
{
    if (on)
        viewAction_ |= action;
    else
        viewAction_ &= ~action;
}

void AndromedaView::clearViewAction(unsigned int action)
{
    setViewAction(action, false);
}

bool AndromedaView::checkViewAction(unsigned int action)
{
    return (viewAction_ & action) > 0;
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
