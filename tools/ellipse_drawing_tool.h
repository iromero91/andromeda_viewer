#ifndef ELLIPSE_DRAWING_TOOL
#define ELLIPSE_DRAWING_TOOL

#include "tool_base.h"
#include "shapes/ellipse.h"

class EllipseDrawingTool : public AToolBase
{
    Q_OBJECT

public:
    EllipseDrawingTool(QObject *parent = 0);

    void paintTool(QPainter *painter, const QRectF &rect);
    void paintHints(QPainter *painter, const QRectF &rect);

    void setCenter(QPointF point) { center_ = point; }

    bool onMousePress(QMouseEvent *event, QPointF cursorPos);
    bool onMouseMove(QPointF cursorPos);

    void getEllipse(AEllipse &ellipse);

protected:
    QPointF center_;
    double rx_ = 0;
    double ry_ = 0;
};

#endif // ELLIPSE_DRAWING_TOOL

