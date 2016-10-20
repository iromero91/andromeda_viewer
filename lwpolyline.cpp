#include "lwpolyline.h"

#include <qmath.h>

#include <QPen>
#include <QBrush>
#include <QPainter>
#include <QStyleOptionGraphicsItem>

#include <QDebug>

LWPolyline::LWPolyline() :
    thickness_(1.5),
    filled_(true)
{

}

QRectF LWPolyline::boundingRect() const
{
    if (points_.count() == 0)
        return QRectF();

    QRectF rect(points_.first().point.x(), points_.first().point.y(), 0, 0);

    QPointF p;

    for (int i=1;i<points_.count();i++)
    {
        p = points_.at(i).point;

        rect.setLeft(fmin(rect.left(), p.x()));
        rect.setRight(fmax(rect.right(), p.x()));

        rect.setTop(fmin(rect.top(), p.y()));
        rect.setBottom(fmax(rect.bottom(), p.y()));
    }

    rect.adjust(-thickness_,
                -thickness_,
                 thickness_,
                 thickness_);

    return rect;
}

void LWPolyline::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QPainterPath path = shape();

    QColor c(200,50,50);

    if (!isClosed())
    {
        c.setRgb(150,180,200);
    }

    if (isSelected())
    {
        c = c.dark(100);
    }

    QPen pen(c);
    pen.setWidthF(thickness_);
    pen.setJoinStyle(Qt::RoundJoin);
    pen.setCapStyle(Qt::RoundCap);

    painter->setPen(pen);

    if (filled_)
    {
        c.setRgb(250,250,200);

        if (isSelected())
        {
            qDebug() << "selected";
            c = c.dark(100);
        }

        QBrush brush(c);
        painter->setBrush(brush);
    }
    else
    {
        painter->setBrush(Qt::NoBrush);
    }

    painter->drawPath(path);

    // Draw the bounding rect for test porpoises
    painter->setBrush(Qt::NoBrush);
    pen.setWidthF(0.5);
    pen.setColor(QColor(150,150,150,200));
    painter->setPen(pen);

    painter->drawRect(boundingRect());
}

bool LWPolyline::comparePoints(QPointF pA, QPointF pB, double epsilon)
{
    QPointF delta = pB - pA;

    return (fabs(delta.x()) <= epsilon) && (fabs(delta.y()) <= epsilon);
}

bool LWPolyline::isClosed()
{
    // Need at least three points_
    if (points_.count() < 3)
        return false;

    return comparePoints(points_.last().point, points_.first().point);
}

QPainterPath LWPolyline::shape() const
{
    QPainterPath path;

    if (points_.count() == 0)
        return path;

    path.moveTo(points_.first().point);

    QPointF p;

    for (int i=1;i<points_.count();i++)
    {
        //TODO - account for curved lines

        p = points_.at(i).point;

        path.lineTo(p);
    }

    return path;
}

bool LWPolyline::addPoint(LWPolypoint point)
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
    if (comparePoints(point.point, points_.last().point))
        return false;

    points_.append(point);
    return true;
}

bool LWPolyline::addPoint(QPointF point, double angle)
{
    LWPolypoint p;
    p.point = point;

    while (angle < -M_PI) angle += (2 * M_PI);
    while (angle >  M_PI) angle -= (2 * M_PI);

    p.angle = angle;

    return addPoint(p);
}
