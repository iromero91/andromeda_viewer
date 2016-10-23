#include "andromeda_scene.h"
#include <QDebug>

#include <QGraphicsItem>

AndromedaScene::AndromedaScene(QObject *parent) :
    QGraphicsScene(parent),
    bg_color_(0xFF, 0xFF, 0xFF),
    draw_axes_(true),
    layerDisplayMode_((uint8_t) (LAYER_MODE::SHOW_ALL)),
    layerMask_((uint64_t) (LAYER_MASK::ALL))
{
    init();


}

void AndromedaScene::init()
{
    axis_pen_.setColor(QColor(150,150,150,150));
    axis_pen_.setWidth(2);
    axis_pen_.setCapStyle(Qt::RoundCap);
    axis_pen_.setJoinStyle(Qt::RoundJoin);
    axis_pen_.setCosmetic(true);

    grid_pen_.setColor(QColor(150,150,150,200));
    grid_pen_.setWidthF(1.5);
    grid_pen_.setCapStyle(Qt::RoundCap);
    grid_pen_.setJoinStyle(Qt::RoundJoin);
    grid_pen_.setCosmetic(true);
}

void AndromedaScene::setLayerDisplayMode(int mode)
{
    layerDisplayMode_ = mode;
}

/**
 * @brief AndromedaScene::checkLayer
 * Check if the provided layer is visible in the scene layer selection
 * @param layerId
 * @return
 */
bool AndromedaScene::checkLayer(int8_t layerId)
{
    uint64_t layer = LayerIdToMask(layerId);

    return (layerMask_ & layer) > 0;
}

/**
 * @brief AndromedaScene::setLayerMask
 * Force visibility of the given layer mask
 * @param selection
 */
void AndromedaScene::setLayerMask(uint64_t selection)
{
    layerMask_ = selection;

    int8_t itemLayer;

    foreach (QGraphicsItem *item, items())
    {
        if (item == NULL) return;

        itemLayer = getItemLayer(item);

        // Check if the item is on a visible layer
        if (checkLayer(itemLayer))
        {
            item->setVisible(true);
            setItemDepth(item, itemLayer);
        }
        else
        {
            item->setVisible(false);
        }
    }
}

/**
 * @brief AndromedaScene::showLayers
 * @param layers
 * @param show
 */
void AndromedaScene::showLayers(uint64_t layerMask, bool show)
{
    if (show)
    {
        setLayerMask(layerMask_ | layerMask);
    }
    else
    {
        setLayerMask(layerMask_ & ~layerMask);
    }
}

void AndromedaScene::hideLayers(uint64_t layerMask)
{
    showLayers(layerMask, false);
}

void AndromedaScene::showLayer(int8_t layerId, bool show)
{
    showLayers(LayerIdToMask(layerId), show);
}

void AndromedaScene::hideLayer(int8_t layerId)
{
    showLayer(layerId, false);
}

void AndromedaScene::drawBackground(QPainter *painter, const QRectF &rect)
{
    if (painter == NULL) return;

    painter->fillRect(rect, bg_color_);

    if (draw_axes_)
    {
        painter->setPen(axis_pen_);

        double x = grid_.getOrigin().x();
        double y = grid_.getOrigin().y();

        // Draw vertical axis
        if ((rect.left() <= x) && (rect.right() >= x))
        {
            painter->drawLine(x, rect.top()-1, x, rect.bottom()+1);
        }

        // Draw horizontal axis
        if ((rect.top() <= y) && (rect.bottom() >= y))
        {
            painter->drawLine(rect.left()-1, y, rect.right()+1, y);
        }
    }

    double grid = grid_.getMajorTick();

    // Limit the number of grids that will be drawn on the screen
    while ((rect.width() > (50 * grid)) || (rect.height() > (50 * grid)))
    {
        grid *= 2;
    }

    painter->setPen(grid_pen_);

    long int x_min = (long int) (rect.left() / grid) - 1;
    long int x_max = (long int) (rect.right() / grid) + 1;

    long int y_min = (long int) (rect.top() / grid) - 1;
    long int y_max = (long int) (rect.bottom() / grid) + 1;

    /* Draw line grid
    // Draw vertical grid lines
    for (long int i=x_min; i<x_max; i++)
    {
        if (i == 0) continue; // Skip major axis

        painter->drawLine(i*grid, rect.top()-1, i*grid, rect.bottom()+1);

    }

    // Draw horizontal grid lines
    for (long int j=y_min; j<y_max; j++)
    {
        if (j == 0) continue;

        painter->drawLine(rect.left()-1, j*grid, rect.right()+1, j*grid);
    }
    */

    for (long int i=x_min;i<x_max;i++)
    {
        for (long int j=y_min;j<y_max;j++)
        {
            painter->drawPoint(i*grid, j*grid);
        }
    }
}

/**
 * @brief AndromedaScene::getItemLayer
 * Return the layer ID of the selected item
 * The layer ID corresponds to how the item will be displayed in the scene
 * @param item - pointer to the item in question
 * @return the layer of the item (or LAYER::NONE if there was an error)
 */
int8_t AndromedaScene::getItemLayer(QGraphicsItem *item)
{
    if (item == NULL) return (int8_t) LAYER_ID::NONE;

    bool ok = false;

    int8_t layer = (int8_t) item->data((int) DRAWABLE_KEY::ITEM_LAYER).toInt(&ok);

    return ok ? layer : (int8_t) LAYER_ID::NONE;
}

/**
 * @brief AndromedaScene::setItemLayer
 * Set the layer ID of the selected item
 * @param item
 * @param layer
 */
void AndromedaScene::setItemLayer(QGraphicsItem *item, int8_t layer)
{
    if (item == NULL) return;

    item->setData((int) DRAWABLE_KEY::ITEM_LAYER, layer);
}

/**
 * @brief AndromedaScene::setItemDepth
 * Set the Z-Order of a given item, based on it's logical layer assignment
 * @param item is a pointer to the item
 * @param layer is the item's logical layer
 * @param flip determines whether the scene view is 'flipped' or not
 */
void AndromedaScene::setItemDepth(QGraphicsItem *item, int8_t layer, bool flip)
{
    if (item == NULL) return;

    // If the layer is the selected layer, force it to the top
    if (layer == getCurrentLayer())
        layer = (int8_t) LAYER_ID::SELECTED;

    //TODO improve this (simplistic) view flipping
    else if (flip)
        layer *= -1;

    item->setZValue(layer);

}

void AndromedaScene::setItemDepth(QGraphicsItem *item, bool flip)
{
    if (item == NULL) return;

    setItemDepth(item, getItemLayer(item), flip);
}
