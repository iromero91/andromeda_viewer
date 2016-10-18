#include "andromeda_view.h"

AndromedaView::AndromedaView(QWidget *parent) : QGraphicsView(parent)
{
    setMouseTracking(true);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
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
