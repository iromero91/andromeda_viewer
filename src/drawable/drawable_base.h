#ifndef DRAWABLE_BASE_H
#define DRAWABLE_BASE_H

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

#include "src/layers/layer_defines.h"
#include "src/shapes/shape_defines.h"
#include "src/geometry/bounding_box.h"

#include "src/base/andromeda_object.h"

class ADrawableBase : public AndromedaObject, public QGraphicsItem
{
    Q_OBJECT

    Q_INTERFACES( QGraphicsItem )

    // Generic drawable properties that we want exposed
    Q_PROPERTY( int layer READ layer WRITE setLayer NOTIFY layerChanged)
    Q_PROPERTY( QPointF pos READ pos WRITE setPos)
    Q_PROPERTY( QRectF boundingBox READ boundingRect STORED false)

public:
    ADrawableBase(QObject *parent = 0);

    // JSON params
    virtual void decode(QJsonObject &json, bool undoable = false);
    virtual void encode(QJsonObject &json) const;

    // Bounding box drawing
    void drawBoundingBox(QPainter *painter);

    // Property getters
    QRectF boundingRect(void) { return QRectF(); }
    int layer(void) const { return layer_; }

    //QPen getBoundingBoxPen(void) { return bounding_box_pen_; }

    // Return a list of 'anchors' for this item
    // Default, empty list

    virtual QPointF centroid(void) { return boundingRect().center(); }
    //TODO
    //QList<QPointF> getAnchors() { return QList<QPointF>(); }

public slots:
    void setLayer(int layer);
    void setBoundingBoxPen(QPen pen) { bounding_box_pen_ = pen; }

signals:
    void layerChanged(int layer);

protected:
    // Properties unique to ADrawableBase
    bool draw_bounding_box_ = false;
    QPen bounding_box_pen_;

    int layer_ = (int)  LAYER_ID::NONE;

};

#endif // DRAWABLE_BASE_H

