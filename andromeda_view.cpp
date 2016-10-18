#include "andromeda_view.h"
#include "andromeda_grid.h"

#include <QScrollBar>
#include <QGraphicsItem>
#include <QDebug>

AndromedaView::AndromedaView(QWidget *parent) :
    QGraphicsView(parent),
    drawOverlay_(false),
    drawCursor_(true)
{
    setMouseTracking(true);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOn);

    setRenderHint(QPainter::Antialiasing);
    setRenderHint(QPainter::HighQualityAntialiasing);
    setRenderHint(QPainter::TextAntialiasing);

    setDragMode(QGraphicsView::RubberBandDrag);
    setViewportUpdateMode(QGraphicsView::SmartViewportUpdate);
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

        double dx, dy = 0;

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
    case Qt::Key_Left:
        moveCursor(-offset,0,true);
        break;
    case Qt::Key_Right:
        moveCursor(offset,0,true);
        break;
    case Qt::Key_Up:
        moveCursor(0,-offset,true);
        break;
    case Qt::Key_Down:
        moveCursor(0,offset,true);
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
    if (event == NULL) return;

    float zoom = (float) event->delta() * 0.01f;

    // Account for 'negative' zoom
    if (zoom < 0)
        zoom = -1.0 / zoom;

    scaleRelative(zoom);

    event->accept();
}

void AndromedaView::mousePressEvent(QMouseEvent *event)
{
    if (event == NULL) return;

    setCursorPos(mapToScene(event->pos()));

    QGraphicsItem *item = getScene()->itemAt(cursorPos_, QTransform());

    if (item != NULL)
    {
        if (event->modifiers() & Qt::ControlModifier)
            item->setSelected(!item->isSelected());
        else
        {
            // Deselect all selected items
            foreach (QGraphicsItem *i, getScene()->selectedItems())
            {
                if (i == NULL) continue;

                i->setSelected(false);
            }

            item->setSelected(true);
        }
    }
    else // Deselect all items
    {
        getScene()->clearSelection();
    }

    if (!event->isAccepted())
    {
        QGraphicsView::mousePressEvent(event);
    }
}

void AndromedaView::mouseReleaseEvent(QMouseEvent *event)
{
    if (event == NULL) return;

    if (!event->isAccepted())
    {
        QGraphicsView::mouseReleaseEvent(event);
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

        event->accept();
    }
    else
    {
        panning = false;
    }

    if (!event->isAccepted())
    {
        QGraphicsView::mouseMoveEvent(event);
    }
}

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
}

void AndromedaView::paintEvent(QPaintEvent *event)
{
    if (event == NULL) return;

    // First perform scene painting
    QGraphicsView::paintEvent(event);

    // Grab the painter
    QPainter painter(viewport());

    // Draw the cursor
    if (drawCursor_) drawCursor(&painter, event->rect());

    if (drawOverlay_) drawOverlay(&painter, event->rect());
}

void AndromedaView::drawOverlay(QPainter *painter, QRect rect)
{
}

void AndromedaView::drawCursor(QPainter *painter, QRect rect)
{
    if (painter == NULL) return;

#define CURSOR 10

    QPoint viewPos = mapFromScene(cursorPos_);

    QPen p;
    p.setWidth(1);

    painter->setPen(p);

    int x = viewPos.x();
    int y = viewPos.y();

    // Is the cursor position in view?
    if ((viewPos.x() > -CURSOR) &&
        (viewPos.x() < (width() + CURSOR)) &&
        (viewPos.y() > -CURSOR) &&
        (viewPos.y() < (height() + CURSOR)))
    {
        painter->drawLine(x-CURSOR,y,x+CURSOR,y);
        painter->drawLine(x,y-CURSOR,x,y+CURSOR);
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
