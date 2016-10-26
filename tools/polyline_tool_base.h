#ifndef POLYLINE_TOOL_BASE_H
#define POLYLINE_TOOL_BASE_H

#include "tool_base.h"
#include "shapes/polyline.h"

class PolylineToolBase : public AToolBase
{
    Q_OBJECT

public:
    PolylineToolBase(QObject *parent = 0);

    virtual APolyline* getPolyline(void);

    virtual bool addPoint(QPointF point) { Q_UNUSED(point); return false; }

    void nextAction(void);

    void paintTool(QPainter *painter, const QRectF &rect);
    void paintHints(QPainter *painter, const QRectF &rect);

protected:
    void onReset(void);

    QPointF start_pos_;
    QList<QPointF> points_;
};

#endif // POLYLINE_TOOL_BASE_KH

