#include <QPen>
#include <QPainter>
#include <QStyleOptionGraphicsItem>
#include <QDebug>
#include <QGraphicsObject>

#include "drawable.h"

ADrawable::ADrawable(QObject *parent) :
    AndromedaObject(parent),
    QGraphicsItem()
{
    setObjectName("AndromedaDrawable");

    /* Configure default pens */

    // Line pen
    line_pen_.setColor(SYMBOL_LINE_COLOR);
    line_pen_.setWidthF(thickness_);
    line_pen_.setJoinStyle(Qt::RoundJoin);
    line_pen_.setCapStyle(Qt::RoundCap);

    // Bounding Box Pen
    bounding_box_pen_.setColor(SYMBOL_BB_COLOR);
    bounding_box_pen_.setWidthF(0.5);
    bounding_box_pen_.setJoinStyle(Qt::RoundJoin);
    bounding_box_pen_.setCapStyle(Qt::RoundCap);
    bounding_box_pen_.setStyle(Qt::DashLine);

    // Fill brush
    fill_brush_.setColor(SYMBOL_FILL_COLOR);

    setFlags(ItemIsSelectable | ItemIsFocusable);
    setAcceptHoverEvents(true);
}

void ADrawable::setLineThickness(double thickness)
{
    //TODO check thickness against limits
    thickness_ = thickness;
}

void ADrawable::drawBoundingBox(QPainter *painter)
{
    if (nullptr == painter) return;

    painter->setPen(bounding_box_pen_);
    painter->setBrush(Qt::NoBrush);

    QRectF r = boundingRect();

    double t = thickness_ / 2;

    r.adjust(t,t,-t,-t);

    painter->drawRect(r);
}

/**
 * @brief ADrawable::setLayer
 * Set the associated layer for this item
 * @param layer
 */
void ADrawable::setLayer(int8_t layer)
{
    setData((int) DRAWABLE_KEY::ITEM_LAYER, layer);
}

/**
 * @brief ADrawable::getLayer
 * Get the layer associated with this item
 * @return
 */
int8_t ADrawable::getLayer()
{
    bool ok = false;

    int8_t layer = (int8_t) data((int) DRAWABLE_KEY::ITEM_LAYER).toInt(&ok);

    return ok ? layer : (int8_t) LAYER_ID::NONE;
}


