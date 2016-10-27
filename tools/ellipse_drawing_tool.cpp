#include "ellipse_drawing_tool.h"

#include <QApplication>

EllipseDrawingTool::EllipseDrawingTool(QObject *parent) : AToolBase(parent)
{

}

void EllipseDrawingTool::paintTool(QPainter *painter, const QRectF &rect)
{
    Q_UNUSED(rect);

    if (nullptr == painter)
        return;

    painter->setBrush(tool_brush_);
    painter->setPen(tool_pen_);

    switch(getToolState())
    {
    case TOOL_STATE::ELLIPSE_SET_POINT:
        painter->drawEllipse(ellipse_.pos(), ellipse_.rx(), ellipse_.ry());
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
        // Draw line towards tool_pos, enscribed on the ellipse
        // TODO
        painter->setPen(hints_pen_);
        painter->drawLine(ellipse_.pos(), tool_pos_);
        break;
    default:
        break;
    }
}

void EllipseDrawingTool::nextAction()
{
    switch (getToolState())
    {
    case TOOL_STATE::RESET:
    case TOOL_STATE::ELLIPSE_SET_CENTER:
        setCenter(tool_pos_);
        setToolState(TOOL_STATE::ELLIPSE_SET_POINT);
        break;
    case TOOL_STATE::ELLIPSE_SET_POINT:
        finish();
        break;
    default:
        break;
    }
}

void EllipseDrawingTool::onToolPosChanged()
{
    QPointF delta = tool_pos_ - ellipse_.pos();

    double x = fabs(delta.x());
    double y = fabs(delta.y());

    if (QApplication::keyboardModifiers() & Qt::ControlModifier)
    {
        x = qMax(x,y);
        y = x;
    }

    setRadius(x,y);
}

void EllipseDrawingTool::getEllipse(AEllipse &ellipse)
{
    ellipse.setPos(ellipse_.pos());
    ellipse.setRadius(ellipse_.radius());
}
