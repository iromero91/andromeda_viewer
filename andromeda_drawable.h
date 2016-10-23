#ifndef ANDROMEDA_DRAWABLE_H
#define ANDROMEDA_DRAWABLE_H

#include <QGraphicsItem>
#include <QList>
#include <QPointF>
#include <QColor>
#include <QPen>
#include <QBrush>

static const QColor SYMBOL_LINE_COLOR(200,50,50);
static const QColor SYMBOL_FILL_COLOR(250,250,200);
static const QColor SYMBOL_BB_COLOR(150,150,150,150);

static const double SYMBOL_LINE_WIDTH_DEFAULT = 1.5f;

class AndromedaDrawable : public QGraphicsItem
{

public:
    AndromedaDrawable();

    void drawBoundingBox(QPainter *painter);

    void setLineThickness(double thickness);
    double getLineThickness(void) { return thickness_; }

    void setFilled(bool filled) { filled_ = filled; }
    bool isFilled(void) { return filled_; }

    // Pen functions
    QPen getLinePen(void) { return linePen_; }
    void setLinePen(QPen pen) { linePen_ = pen; }

    QPen getBoundingBoxPen(void) { return boundingBoxPen_; }
    void setBoundingBoxPen(QPen pen) { boundingBoxPen_ = pen; }

    QBrush getFillBrush(void) { return fillBrush_; }
    void setFillBrush(QBrush brush) { fillBrush_ = brush; }

protected:
    double thickness_;  // Line thickness
    bool filled_;       // Is the shape filled?
    bool drawBoundingBox_;

    QPen linePen_;
    QPen boundingBoxPen_;

    QBrush fillBrush_;

};

#endif // ANDROMEDA_DRAWABLE_H

