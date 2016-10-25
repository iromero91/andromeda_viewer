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
#include "geometry/bounding_box.h"

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
    QPen getLinePen(void) { return line_pen_; }
    void setLinePen(QPen pen) { line_pen_ = pen; }

    QPen getBoundingBoxPen(void) { return bounding_box_pen_; }
    void setBoundingBoxPen(QPen pen) { bounding_box_pen_ = pen; }

    QBrush getFillBrush(void) { return fill_brush_; }
    void setFillBrush(QBrush brush) { fill_brush_ = brush; }

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

    QPen line_pen_;
    QPen bounding_box_pen_;

    QBrush fill_brush_;

};

#endif // SHAPES_DRAWABLE_H

