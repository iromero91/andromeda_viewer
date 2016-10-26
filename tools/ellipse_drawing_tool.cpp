#include "ellipse_drawing_tool.h"

#include <QApplication>

EllipseDrawingTool::EllipseDrawingTool(QObject *parent) : AToolBase(parent)
{

}

void EllipseDrawingTool::paintTool(QPainter *painter, const QRectF &rect)
{
    Q_UNUSED(rect);

    if (painter == nullptr)
        return;

    painter->setBrush(tool_brush_);
    painter->setPen(tool_pen_);

    switch(getToolState())
    {
    case TOOL_STATE::ELLIPSE_SET_POINT:
        painter->drawEllipse(center_, rx_, ry_);
        break;
    default:
        break;
    }
}

void EllipseDrawingTool::paintHints(QPainter *painter, const QRectF &rect)
{
    Q_UNUSED(rect);

    switch (getToolState())
    {
    case TOOL_STATE::ELLIPSE_SET_POINT:
        // Draw line to current mouse position
        painter->setPen(hints_pen_);
        painter->drawLine(center_, tool_pos_);
        break;
    default:
        break;
    }
}

bool EllipseDrawingTool::onMousePress(QMouseEvent *event, QPointF cursorPos)
{
    if (event->button() == Qt::LeftButton)
    {
        switch (getToolState())
        {
        default:
        case TOOL_STATE::ELLIPSE_SET_CENTER:
            setCenter(cursorPos);
            setToolState(TOOL_STATE::ELLIPSE_SET_POINT);
            break;
        case TOOL_STATE::ELLIPSE_SET_POINT:
            finish();
            break;
        }

        emit updated();

        return true;
    }
    return false;
}

bool EllipseDrawingTool::onMouseMove(QPointF cursorPos)
{
    AToolBase::onMouseMove(cursorPos);

    if (getToolState() == TOOL_STATE::ELLIPSE_SET_POINT)
    {
        QPointF delta = cursorPos - center_;

        double x = fabs(delta.x());
        double y = fabs(delta.y());

        if (QApplication::keyboardModifiers() & Qt::ControlModifier)
        {
            x = qMax(x,y);
            y = x;
        }

        rx_ = x;
        ry_ = y;
    }

    emit updated();

    return true;
}

void EllipseDrawingTool::getEllipse(AEllipse &ellipse)
{
    ellipse.setPos(center_);
    ellipse.setRadius(rx_, ry_);
}
