#include "polyline.h"

#include <qmath.h>

#include <QPen>
#include <QBrush>
#include <QPainter>
#include <QStyleOptionGraphicsItem>

#include <QDebug>

APolyline::APolyline() :
    ADrawable()
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

void APolyline::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
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

bool APolyline::comparePoints(QPointF pA, QPointF pB, double epsilon)
{
    QPointF delta = pB - pA;

    return (fabs(delta.x()) <= epsilon) && (fabs(delta.y()) <= epsilon);
}

bool APolyline::isClosed()
{
    // Need at least three points_
    if (points_.count() < 3)
        return false;

    return comparePoints(points_.last().point, points_.first().point);
}

QPainterPath APolyline::shape() const
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
    if (comparePoints(point.point, points_.last().point))
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
