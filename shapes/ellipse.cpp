#include "ellipse.h"

#include <math.h>

AEllipse::AEllipse() : ADrawable()
{
    setObjectName("AndromedaEllipse");
}

QRectF AEllipse::boundingRect() const
{
    QRectF rect(-rx_, -ry_, 2*rx_, 2*ry_);

    rect.adjust(-thickness_,
                -thickness_,
                 thickness_,
                 thickness_);

    return rect;
}

QPainterPath AEllipse::shape() const
{
    QPainterPath path;

    path.addEllipse(QPointF(0,0), rx_, ry_);

    return path;
}

void AEllipse::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(widget);

    QPen pen = line_pen_;
    QBrush brush = fill_brush_;

    QColor c = line_pen_.color();

    if (isSelected())
        c = c.dark();

    c = (option->state & QStyle::State_MouseOver) ? c.light() : c;

    pen.setColor(c);

    painter->setPen(pen);

    /*
    if (filled_)
    {
        c = brush.color();

        if (isSelected())
            c = c.dark();

        brush.setColor(c);

        painter->setBrush(brush);
    }
    else
    {
        painter->setBrush(Qt::NoBrush);
    }
    */
    painter->setBrush(QBrush(SYMBOL_FILL_COLOR));

    painter->drawEllipse(QPointF(0,0), rx_, ry_);

    if (drawBoundingBox_)
        drawBoundingBox(painter);

}

void AEllipse::setRadius(double rx, double ry)
{
    rx_ = fabs(rx);
    ry_ = fabs(ry);

    prepareGeometryChange();

    update();
}

void AEllipse::setRadius(double r)
{
    setRadius(r,r);
}

/*
QList<QPointF> AEllipse::getAnchors()
{
    QList<QPointF> anchors;

    // Center
    anchors.append(pos);

    // Top
    anchors.append(QPointF(pos.x(), pos.y() - ry_));

    // Bottom
    anchors.append(QPointF(pos.x(), pos.y() + ry_));

    // Left
    anchors.append(QPointF(pos.x() - rx_, pos.y()));

    // Right
    anchors.append(QPointF(pos.x() + rx_, pos.y()));

    return anchors;
}
*/
