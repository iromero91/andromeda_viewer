#include "bounding_box.h"

void ABoundingBox::start(QPointF point)
{
    setTopLeft(point);
    setSize(QSizeF(0,0));
}

void ABoundingBox::add(QPointF point)
{
    setLeft(qMin(left(), point.x()));
    setRight(qMax(right(), point.x()));

    setTop(qMin(top(), point.y()));
    setBottom(qMax(bottom(), point.y()));
}

void ABoundingBox::add(QLineF line)
{
    add(line.p1());
    add(line.p2());
}

/*
ABoundingBox ABoundingBox::operator+(const QPointF point)
{
    ABoundingBox box(this->topLeft(), this->size());

    box.add(point);

    return box;
}

inline ABoundingBox &ABoundingBox::operator+=(const QPointF point)
{
    add(point);
    return *this;
}
*/
