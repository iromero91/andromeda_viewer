#include "andromeda_drawable.h"
#include <QPen>
#include <QPainter>
#include <QStyleOptionGraphicsItem>
#include <QDebug>

TestRect::TestRect()
{
    setFlags(ItemIsSelectable | ItemIsFocusable);
    //setFlags(ItemIsFocusable);
    setAcceptHoverEvents(true);

}

QRectF TestRect::boundingRect() const
{
    return QRectF(rect.left()-1, rect.top()-1, rect.width()+2, rect.height()+2);
}

void TestRect::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    if (painter == NULL || option == NULL) return;

    QPen p;

    p.setWidth(2);
    p.setCapStyle(Qt::RoundCap);
    p.setJoinStyle(Qt::RoundJoin);

    QColor c(45,200,115);

    c = (option->state & QStyle::State_Selected) ? c.dark(150) : c;
    c = (option->state & QStyle::State_MouseOver) ? c.light(150) : c;

    p.setColor(c);
    painter->setPen(p);

    painter->setBrush(QBrush(QColor(100,100,100,150)));

    painter->drawRect(rect);

}

void TestRect::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    //QGraphicsItem::mouseMoveEvent(event);
}

void TestRect::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    //QGraphicsItem::mousePressEvent(event);
    //update();
}

void TestRect::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    //QGraphicsItem::mouseReleaseEvent(event);
    //update();
}
