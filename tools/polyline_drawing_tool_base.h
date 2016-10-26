#ifndef POLYLINE_DRAWING_TOOL_BASE_H
#define POLYLINE_DRAWING_TOOL_BASE_H

#include "tool_base.h"
#include "shapes/polyline.h"

class PolylineDrawingToolBase : public AToolBase
{
    Q_OBJECT

public:
    PolylineDrawingToolBase(QObject *parent = 0);

    void getPolyline(APolyline &polyline);

    void paintTool(QPainter *painter, const QRectF &rect);
    void paintHints(QPainter *painter, const QRectF &rect);

    void setStartPos(QPointF point) { start_pos_ = point; }
    virtual bool addPoint(QPointF point);

    bool onMousePress(QMouseEvent *event, QPointF cursorPos);
    bool onMouseDoubleClick(QMouseEvent *event, QPointF cursorPos);

protected:
    void onReset(void);

    QPointF start_pos_;
    QList<QPointF> points_;
};

#endif // POLYLINE_DRAWING_TOOL_BASE_H

