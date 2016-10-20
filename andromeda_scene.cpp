#include "andromeda_scene.h"
#include <QDebug>

AndromedaScene::AndromedaScene(QObject *parent) :
    QGraphicsScene(parent),
    bg_color_(0xFF, 0xFF, 0xFF),
    draw_axes_(true)
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
