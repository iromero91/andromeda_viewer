#ifndef ANDROMEDA_SCENE_H
#define ANDROMEDA_SCENE_H

#include <QGraphicsScene>
#include <QColor>
#include <QPointF>
#include <QPainter>
#include <QPen>

class AndromedaScene : public QGraphicsScene
{
    Q_OBJECT

public:
    AndromedaScene(QObject *parent = 0);

    void setBackgroundColor(QColor c) { bg_color_ = c;}
    QColor getBackgroundColor() { return bg_color_; }

    void setAxesEnabled(bool draw) { draw_axes_ = draw; }
    bool getAxesEnabled() { return draw_axes_; }

    void setOrigin(QPointF origin) { origin_ = origin; }
    QPointF getOrigin() { return origin_; }

    void drawBackground(QPainter *painter, const QRectF &rect);

protected:
    void init();

    QColor bg_color_;   // Background color for the scene
    bool draw_axes_;    // Flag for displaying axes
    QPointF origin_;    // Scene origin

    QPen axis_pen_;     // Pen object for drawing the axes
};


#endif // ANDROMEDA_SCENE_H

