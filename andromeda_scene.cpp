#include "andromeda_scene.h"

AndromedaScene::AndromedaScene(QObject *parent) :
    QGraphicsScene(parent),
    bg_color_(0xFF, 0xFF, 0xFF),
    draw_axes_(true),
    origin_(0,0)
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
}

void AndromedaScene::drawBackground(QPainter *painter, const QRectF &rect)
{
    if (painter == NULL) return;

    painter->fillRect(rect, bg_color_);

    if (draw_axes_)
    {
        painter->setPen(axis_pen_);

        double x = origin_.x();
        double y = origin_.y();

        // Draw vertical axis
        if ((rect.left() <= x) && (rect.right() >= x))
        {
            painter->drawLine(x, rect.top()-1, x, rect.bottom()+1);
        }

        // Draw horizontal axis
        if ((rect.top() <= y) && (rect.right() >= y))
        {
            painter->drawLine(rect.left()-1, y, rect.right()+1, y);
        }
    }

    //TODO - draw grid
}
