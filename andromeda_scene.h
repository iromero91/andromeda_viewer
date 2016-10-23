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

    void setLayerSelection(quint64 selection);

    void setCurrentLayer(quint64 layer);
    quint64 getCurrentLayer() { return currentLayer_; }

    void showLayers(quint64 layers, bool show = true);
    void hideLayers(quint64 layers);

    void showAllLayers() { setLayerSelection((quint64) LAYER::NONE); }
    void hideAllLayers() { setLayerSelection((quint64) LAYER::ALL); }

    quint64 getItemLayer(QGraphicsItem *item);
    void setItemLayer(QGraphicsItem *item, quint64 layer);

protected:
    void init();

    QColor bg_color_;   // Background color for the scene
    bool draw_axes_;    // Flag for displaying axes

    QPen axis_pen_;     // Pen object for drawing the axes
    QPen grid_pen_;     // Pen object for drawing the grid

    AndromedaGrid grid_;    // Grid object

    uint8_t layerDisplayMode_;  // How to display multiple layers
    quint64 layerSelection_;   // Which layers are currently visible
    quint64 currentLayer_;     // Which layer is currently selected (top)

};


#endif // ANDROMEDA_SCENE_H

