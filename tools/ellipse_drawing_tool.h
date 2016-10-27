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

    void setCenter(QPointF point) { ellipse_.setPos(point); }
    void setRadius(double rx, double ry) { ellipse_.setRadius(rx, ry); }

    virtual void getEllipse(AEllipse &ellipse);

    void nextAction(void);

protected:
    AEllipse ellipse_;

    void onToolPosChanged(void);
};

#endif // ELLIPSE_DRAWING_TOOL

