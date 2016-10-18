#include "andromeda_view.h"
#include "andromeda_grid.h"

#include <QScrollBar>

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
void AndromedaView::setCursorPos(QPointF pos)
{
    double grid = getScene()->getGrid().getMajorTick();

    pos = AndromedaGrid::mapToGrid(pos, QPointF(grid,grid));

    if ((pos.x() != cursorPos_.x()) || (pos.y() != cursorPos_.y()))
    {
        emit cursorPositionChanged(pos);
    }

    cursorPos_ = pos;
}

void AndromedaView::moveCursor(QPointF offset)
{
    setCursorPos(cursorPos_ + offset);
}

void AndromedaView::moveCursor(double dx, double dy)
{
    moveCursor(QPointF(dx,dy));
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

            horizontalScrollBar()->setValue(horizontalScrollBar()->value() - delta.x());
            verticalScrollBar()->setValue(verticalScrollBar()->value() - delta.y());

            scene()->update();
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
}

void AndromedaView::paintEvent(QPaintEvent *event)
{
    if (event == NULL) return;

    // First perform scene painting
    QGraphicsView::paintEvent(event);

    // Grab the painter
    QPainter painter(viewport());

    // Draw the cursor
    if (draw_cursor_) drawCursor(&painter, event->rect());

    if (draw_overlay_) drawOverlay(&painter, event->rect());
}

void AndromedaView::drawOverlay(QPainter *painter, QRect rect)
{
}

void AndromedaView::drawCursor(QPainter *painter, QRect rect)
{

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
                mapToScene(width()-1, height()-1)
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
