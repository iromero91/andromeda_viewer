#ifndef BOUNDING_BOX_H
#define BOUNDING_BOX_H

#include <QRectF>
#include <QLineF>

/**
 * @brief The ABoundingBox class
 * Extends the functionality of QRectF to provide extra bounding box features
 */

class ABoundingBox : public QRectF
{
public:
    ABoundingBox(void) : QRectF() {}
    ABoundingBox(const QRectF &rect) : QRectF(rect) {}
    ABoundingBox(const QPointF &topLeft, const QSizeF &size) : QRectF(topLeft, size) {}
    ABoundingBox(const QPointF &topLeft, const QPointF &bottomRight) : QRectF(topLeft, bottomRight) {}
    ABoundingBox(QPointF point) : QRectF(point, QSizeF(0,0)) {}
    ABoundingBox(qreal left, qreal top, qreal width, qreal height) : QRectF(left, top, width, height) {}

    void start(QPointF point);

    void add(QPointF point);
    void add(QLineF line);

    //TODO something is wrong here
    //ABoundingBox operator+(const QPointF point);
    //inline ABoundingBox &operator+=(const QPointF point);

};

#endif // BOUNDING_BOX_H

