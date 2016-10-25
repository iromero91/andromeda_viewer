#include "polyline.h"
#include "geometry/geometry.h"

#include <qmath.h>

#include <QPen>
#include <QBrush>
#include <QPainter>
#include <QStyleOptionGraphicsItem>

#include <QDebug>

APolyline::APolyline() : ADrawable()
{
}

LWPolypoint APolyline::getPolypoint(int index)
{
    if (index >= points_.count())
    {
        LWPolypoint p;
        p.point = QPointF();
        p.angle = 0;

        return p;
    }

    return points_.at(index);
}

QPointF APolyline::getPoint(int index)
{
    return getPolypoint(index).point;
}

double APolyline::getAngle(int index)
{
    return getPolypoint(index).angle;
}

void APolyline::setPoint(int index, QPointF point)
{
    if (index < points_.count())
    {
        LWPolypoint p = points_.at(index);
        p.point = point;
        points_.replace(index, p);
    }
}

void APolyline::setAngle(int index, double angle)
{
    if (index < points_.count())
    {
        LWPolypoint p = points_.at(index);
        p.angle = angle;
        points_.replace(index, p);
    }
}

QRectF APolyline::boundingRect() const
{
    if (points_.count() == 0)
        return QRectF();

    QRectF rect(start_pos_, QSizeF(0,0));

    for (int i=0; i<points_.count(); i++)
    {
        rect = rect.united(QRectF(points_.at(i).point, QSizeF(0,0)));
    }

    rect.adjust(-thickness_,
                -thickness_,
                 thickness_,
                 thickness_);

    return rect;
}

void APolyline::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(widget);

    QPainterPath path = shape();

    QPen pen = linePen_;
    QBrush brush = fillBrush_;

    QColor c = linePen_.color();

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
        {
            c = c.dark();
        }

        brush.setColor(c);

        painter->setBrush(brush);
    }
    */
    if (isClosed())
    {
        painter->setBrush(QBrush(SYMBOL_FILL_COLOR));
    }
    else
    {
        painter->setBrush(Qt::NoBrush);
    }

    painter->drawPath(path);

    if (drawBoundingBox_)
        drawBoundingBox(painter);
}

bool APolyline::isClosed()
{
    // Need at least three points (including starting position)
    if (points_.count() < 2)
        return false;

    return AGeometry::PointsAreCoincident(points_.last().point, start_pos_);
}

QPainterPath APolyline::shape() const
{
    QPainterPath path;

    path.moveTo(start_pos_);

    for (int i=0; i<points_.count(); i++)
    {
        path.lineTo(points_.at(i).point);
    }

    return path;
}

bool APolyline::addPoint(LWPolypoint point)
{
    // Enforce zero-angle for the first point, doesn't make sense
    if (points_.count() == 0)
    {
        point.angle = 0;

        points_.append(point);
        return true;
    }

    // Can't add more points_ to a closed line
    if (isClosed())
        return false;

    // New point is the same!
    if (AGeometry::PointsAreCoincident(point.point, points_.last().point))
        return false;

    points_.append(point);

    prepareGeometryChange();

    return true;
}

bool APolyline::addPoint(QPointF point, double angle)
{
    LWPolypoint p;
    p.point = point;

    while (angle < -M_PI) angle += (2 * M_PI);
    while (angle >  M_PI) angle -= (2 * M_PI);

    p.angle = angle;

    return addPoint(p);
}
