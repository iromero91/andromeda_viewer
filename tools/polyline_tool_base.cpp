#include "polyline_tool_base.h"

PolylineToolBase::PolylineToolBase(QObject *parent) : AToolBase(parent)
{

}

void PolylineToolBase::onReset()
{
    polyline_.clear();
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

    painter->setPen(tool_pen_);
    painter->setBrush(Qt::NoBrush);

    if (polyline_.shape().intersects(rect))
    {
        painter->drawPath(polyline_.shape());

        if (getToolState() == TOOL_STATE::POLYLINE_ADD_POINT)
        {
            painter->drawLine(polyline_.endPoint(), tool_pos_);
        }

        polyline_.drawBoundingBox(painter);
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
        painter->drawLine(polyline_.startPoint(), tool_pos_);
    }
}

void PolylineToolBase::getPolyline(APolyline &line)
{
    line.clear();

    for (int i=0; i<polyline_.pointCount(); i++)
    {
        line.addPoint(polyline_.point(i));
    }

    if (force_closed_)
    {
        line.close();
    }

    // Re-center the polyline around its own center
    line.normalize();
}
