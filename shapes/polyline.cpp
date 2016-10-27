#include "polyline.h"
#include "geometry/geometry.h"

#include <qmath.h>

#include <QPen>
#include <QBrush>
#include <QPainter>
#include <QStyleOptionGraphicsItem>

#include <QDebug>

APolyline::APolyline(QObject *parent) : ADrawablePrimitive(parent)
{
    setObjectName("APolyline");
}

QPointF APolyline::endPoint()
{
    if (points_.count() == 0)
    {
        return start_pos_;
    }
    else
    {
        return points_.last().point;
    }
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

    ABoundingBox box(start_pos_);

    for (int i=0; i<points_.count(); i++)
    {
        box.add(points_.at(i).point);
    }

    double offset = line_width_ / 2;

    box.adjust(-offset,
               -offset,
                offset,
                offset);

    return QRectF(box);
}

void APolyline::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(widget);

    QPainterPath path = shape();

    painter->setPen(pen(option));
    painter->setBrush(brush(option));

    painter->drawPath(path);

    if (draw_bounding_box_)
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

void APolyline::close()
{
    if (isClosed()) return;

    addPoint(startPoint());
}

/**
 * @brief APolyline::normalize
 * Recenter the polyline at the bounding box centroid
 * Adjust each point accordingly
 */
void APolyline::normalize()
{
    QPointF center = centroid();

    start_pos_ -= center;

    setPos(center);
}
