#include "andromeda_drawable.h"
#include <QPen>
#include <QPainter>
#include <QStyleOptionGraphicsItem>
#include <QDebug>

AndromedaDrawable::AndromedaDrawable() :
    QGraphicsItem(),
    thickness_(SYMBOL_LINE_WIDTH_DEFAULT),
    filled_(true),
    drawBoundingBox_(true)
{
    /* Configure default pens */

    // Line pen
    linePen_.setColor(SYMBOL_LINE_COLOR);
    linePen_.setWidthF(thickness_);
    linePen_.setJoinStyle(Qt::RoundJoin);
    linePen_.setCapStyle(Qt::RoundCap);

    // Bounding Box Pen
    boundingBoxPen_.setColor(SYMBOL_BB_COLOR);
    boundingBoxPen_.setWidthF(0.5);
    boundingBoxPen_.setJoinStyle(Qt::RoundJoin);
    boundingBoxPen_.setCapStyle(Qt::RoundCap);
    boundingBoxPen_.setStyle(Qt::DashLine);

    // Fill brush
    fillBrush_.setColor(SYMBOL_FILL_COLOR);

    setFlags(ItemIsSelectable | ItemIsFocusable);
    setAcceptHoverEvents(true);
}

void AndromedaDrawable::setLineThickness(double thickness)
{
    //TODO check thickness against limits
    thickness_ = thickness;
}

void AndromedaDrawable::drawBoundingBox(QPainter *painter)
{
    if (painter == NULL) return;

    painter->setPen(boundingBoxPen_);
    painter->setBrush(Qt::NoBrush);

    QRectF r = boundingRect();

    double t = thickness_ / 2;

    r.adjust(t,t,-t,-t);

    painter->drawRect(r);
}

/**
 * @brief AndromedaDrawable::setLayer
 * Set the associated layer for this item
 * @param layer
 */
void AndromedaDrawable::setLayer(int8_t layer)
{
    setData((int) DRAWABLE_KEY::ITEM_LAYER, layer);
}

/**
 * @brief AndromedaDrawable::getLayer
 * Get the layer associated with this item
 * @return
 */
int8_t AndromedaDrawable::getLayer()
{
    bool ok = false;

    int8_t layer = (int8_t) data((int) DRAWABLE_KEY::ITEM_LAYER).toInt(&ok);

    return ok ? layer : (int8_t) LAYER_ID::NONE;
}


