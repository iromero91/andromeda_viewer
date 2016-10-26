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
#include <QGraphicsItem>

#include "layers/layer_defines.h"
#include "shapes/shape_defines.h"
#include "geometry/bounding_box.h"

#include "base/andromeda_object.h"

class ADrawable : public AndromedaObject, public QGraphicsItem
{
    Q_OBJECT

    // Generic drawable properties that we want exposed
    Q_PROPERTY(int layer READ getLayer WRITE setLayer NOTIFY onLayerChanged)
public:
    ADrawable(QObject *parent = 0);

    void drawBoundingBox(QPainter *painter);
    double getLineThickness(void) { return thickness_; }

    bool isFilled(void) { return filled_; }

    // Pen functions
    QPen getLinePen(void) { return line_pen_; }

    QPen getBoundingBoxPen(void) { return bounding_box_pen_; }

    QBrush getFillBrush(void) { return fill_brush_; }

    // Return a list of 'anchors' for this item
    // Default, empty list
    QList<QPointF> getAnchors() { return QList<QPointF>(); }

    int getLayer(void) { return layer_; }

public slots:
    void setLayer(int layer) { layer_ = layer; }
    void setBoundingBoxPen(QPen pen) { bounding_box_pen_ = pen; }
    void setLinePen(QPen pen) { line_pen_ = pen; }
    void setFilled(bool filled) { filled_ = filled; }
    void setLineThickness(double thickness);
    void setFillBrush(QBrush brush) { fill_brush_ = brush; }


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

    int layer_;

signals:
    void onLayerChanged(int layer);

};

#endif // SHAPES_DRAWABLE_H

