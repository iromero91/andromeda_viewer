#ifndef SHAPES_DRAWABLE_H
#define SHAPES_DRAWABLE_H

#include <QGraphicsItem>
#include <QList>
#include <QPointF>
#include <QColor>
#include <QPen>
#include <QBrush>
#include <QPainter>
#include <QStyleOptionGraphicsItem>
#include <QString>

#include "layers/layer_defines.h"
#include "shapes/shape_defines.h"

class ADrawable : public QGraphicsItem
{

public:
    ADrawable();

    enum DrawableDataDescriptors
    {
        DRAWABLE_TYPE = 0x01,
    };

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

    void setLayer(int8_t layer);
    int8_t getLayer(void);

    // Return a list of 'anchors' for this item
    // Default, empty list
    QList<QPointF> getAnchors() { return QList<QPointF>(); }

protected:
    double thickness_ = SYMBOL_LINE_WIDTH_DEFAULT;  // Line thickness
    bool filled_ = true;       // Is the shape filled?
    bool drawBoundingBox_ = false;

    //TODO
    /*
    QColor getLineColor(void);
    QColor getFillColor(void);
    */

    QPen linePen_;
    QPen boundingBoxPen_;

    QBrush fillBrush_;

};

#endif // SHAPES_DRAWABLE_H

