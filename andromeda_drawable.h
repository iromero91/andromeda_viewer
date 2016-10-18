#ifndef ANDROMEDA_DRAWABLE_H
#define ANDROMEDA_DRAWABLE_H

#include <QGraphicsItem>
#include <QList>
#include <QPointF>

class PinDrawable : public QGraphicsItem
{
public:
    QRectF boundingRect() const Q_DECL_OVERRIDE;

};

class AndromedaDrawable : public QGraphicsItem
{
};

class TestRect : public QGraphicsItem
{
public:
    TestRect();

    QRectF boundingRect() const Q_DECL_OVERRIDE;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) Q_DECL_OVERRIDE;

    QRectF rect;

protected:

    void mouseMoveEvent(QGraphicsSceneMouseEvent *event) Q_DECL_OVERRIDE;
    void mousePressEvent(QGraphicsSceneMouseEvent *event) Q_DECL_OVERRIDE;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) Q_DECL_OVERRIDE;
};

#endif // ANDROMEDA_DRAWABLE_H

