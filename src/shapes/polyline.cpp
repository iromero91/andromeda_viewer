#include "polyline.h"
#include "src/geometry/geometry.h"

#include <qmath.h>

#include <QPen>
#include <QBrush>
#include <QPainter>
#include <QStyleOptionGraphicsItem>

#include <QJsonArray>

#include <QDebug>

APolyline::APolyline(QObject *parent) : ADrawablePrimitive(parent)
{
    setObjectName(OBJECT_NAME::A_DRAWABLE_POLYLINE);
}

APolyline* APolyline::clone()
{
    APolyline *line = new APolyline();

    return line;
}

void APolyline::encode(AJsonObject &data) const
{
    ADrawablePrimitive::encode(data);

    // Remove 'position' key
    data.remove(OBJ_KEY::POS);

    // Points
    QJsonArray jPoints;

    QJsonObject jPoint;

    LWPolypoint p;

    for (int i=0;i<points_.count();i++)
    {
        p = points_.at(i);
        jPoint = AJsonObject::fromPoint(p.point);

        if ((i > 0) && (AGeometry::ArcIsCurved(p.angle)))
            jPoint[OBJ_KEY::ANGLE] = p.angle;

        jPoints.append(jPoint);
    }

    data[OBJ_KEY::POINTS] = jPoints;
}

void APolyline::decode(AJsonObject &data, bool undoable)
{
    ADrawablePrimitive::decode(data, undoable);
}

bool APolyline::allSegmentsAreStraight()
{
    // Ignore the first point's angle
    for (int i=1;i<points_.count();i++)
    {
        if (AGeometry::ArcIsCurved(points_.at(i).angle))
            return false;
    }

    return true;
}

bool APolyline::isSelfIntersecting()
{
    // Two line segments are required for this test
    if (pointCount() <= 3)
        return false;

    QPointF intersection;

    for (int i=0;i<points_.count()-1;i++)
    {
        QLineF A(point(i), point(i+1));

        for (int j=(i+2); j<(points_.count()-1); j++)
        {
            QLineF B(point(j), point(j+1));


            if (A.intersect(B, &intersection) == QLineF::BoundedIntersection)
            {
                return true;
            }
        }
    }

    return false;
}

QPointF APolyline::startPoint() const
{
    if (points_.count() == 0)
        return QPointF();

    return points_.first().point;
}

QPointF APolyline::endPoint() const
{
    if (points_.count() == 0)
        return QPointF();

    return points_.last().point;
}

LWPolypoint APolyline::polypoint(int index)
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

QPointF APolyline::point(int index)
{
    return polypoint(index).point;
}

double APolyline::angle(int index)
{
    return polypoint(index).angle;
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

    QRectF box = shape().controlPointRect();

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

    if (pointCount() < 1)
        return;

    QPainterPath path = shape();

    painter->setPen(pen(option));

    // Straight line segments can't be filled
    if (pointCount() == 2)
        painter->setBrush(Qt::NoBrush);
    else
        painter->setBrush(brush(option));

    painter->drawPath(path);

    if (draw_bounding_box_)
        drawBoundingBox(painter);
}

bool APolyline::isClosed() const
{
    // Need at least three points (including starting position)
    if (points_.count() < 2)
        return false;

    return AGeometry::PointsAreCoincident(startPoint(), endPoint());
}

QPainterPath APolyline::shape() const
{
    QPainterPath path;

    if (points_.count() > 0)
    {
        path.moveTo(startPoint());
    }

    LWPolypoint p;

    for (int i=1; i<points_.count(); i++)
    {
        p = points_.at(i);

        path.lineTo(p.point);
    }

    return path;
}

bool APolyline::addPoint(LWPolypoint point)
{
    // Account for angular rollover
    while (point.angle < -M_PI) point.angle += (2 * M_PI);
    while (point.angle >  M_PI) point.angle -= (2 * M_PI);

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

    for (int i=0; i<points_.count(); i++)
    {
        setPoint(i, point(i) - center);
    }

    setPos(center);
    //moveTo(center);
}
