#ifndef ANDROMEDA_SCENE_H
#define ANDROMEDA_SCENE_H

#include <QGraphicsScene>
#include <QColor>
#include <QPointF>
#include <QPainter>
#include <QPen>

#include <stdint.h>

#include "andromeda_grid.h"
#include "drawable_enums.h"
#include "layer_definitions.h"

class AndromedaScene : public QGraphicsScene
{
    Q_OBJECT

public:
    AndromedaScene(QObject *parent = 0);

    void setBackgroundColor(QColor c) { bg_color_ = c;}
    QColor getBackgroundColor() { return bg_color_; }

    void setAxesEnabled(bool draw) { draw_axes_ = draw; }
    bool getAxesEnabled() { return draw_axes_; }

    void setGrid(AndromedaGrid grid) { grid_ = grid; }
    AndromedaGrid getGrid() { return grid_; }

    void drawBackground(QPainter *painter, const QRectF &rect);

    void setLayerDisplayMode(int mode);
    int getLayerDisplayMode() { return layerDisplayMode_; }

    bool checkLayer(int8_t layerId);

    void setCurrentLayer(int8_t layer);
    int8_t getCurrentLayer() { return currentLayer_; }

    void setLayerMask(uint64_t layers);
    uint64_t getLayerMask() { return layerMask_; }
    void showLayers(uint64_t layerMask, bool show = true);
    void hideLayers(uint64_t layerMask);

    void showLayer(int8_t layerId, bool show = true);
    void hideLayer(int8_t layerId);

    void showAllLayers() { setLayerMask((uint64_t) LAYER_MASK::NONE); }
    void hideAllLayers() { setLayerMask((uint64_t) LAYER_MASK::ALL); }

    int8_t getItemLayer(QGraphicsItem *item);
    void setItemLayer(QGraphicsItem *item, int8_t layer);

    void setItemDepth(QGraphicsItem *item, int8_t layer, bool flip = false);
    void setItemDepth(QGraphicsItem *item, bool flip = false);

protected:
    void init();

    QColor bg_color_;   // Background color for the scene
    bool draw_axes_;    // Flag for displaying axes

    QPen axis_pen_;     // Pen object for drawing the axes
    QPen grid_pen_;     // Pen object for drawing the grid

    AndromedaGrid grid_;    // Grid object

    uint8_t layerDisplayMode_;  // How to display multiple layers
    uint64_t layerMask_;   // Which layers are currently visible

    int8_t currentLayer_;     // Which layer is currently selected (top)

};


#endif // ANDROMEDA_SCENE_H

