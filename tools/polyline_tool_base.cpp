#include "polyline_tool_base.h"

PolylineToolBase::PolylineToolBase(QObject *parent) : AToolBase(parent)
{

}

void PolylineToolBase::onReset()
{
    points_.clear();
}

void PolylineToolBase::nextAction()
{
    if (addPoint(tool_pos_))
    {
        finish();
    }
}

void PolylineToolBase::paintTool(QPainter *painter, const QRectF &rect)
{
    Q_UNUSED(rect);

    if (points_.count() > 0)
    {
        painter->setPen(tool_pen_);

        QPainterPath path(start_pos_);

        foreach (QPointF point, points_)
        {
            path.lineTo(point);
        }

        path.lineTo(tool_pos_);

        if (path.intersects(rect))
        {
            painter->drawPath(path);
        }
    }
}

void PolylineToolBase::paintHints(QPainter *painter, const QRectF &rect)
{
    Q_UNUSED(rect);

    if (nullptr == painter)
        return;

    if (getToolState() == TOOL_STATE::POLYLINE_ADD_POINT)
    {
        painter->setPen(hints_pen_);
        painter->drawLine(start_pos_, tool_pos_);
    }
}

APolyline* PolylineToolBase::getPolyline()
{
    APolyline *poly = new APolyline();

    poly->setStartPos(start_pos_);

    foreach (QPointF p, points_)
    {
        poly->addPoint(p);
    }

    return poly;
}
