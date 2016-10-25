#ifndef POLYLINE_TOOL_H
#define POLYLINE_TOOL_H

#include "tool_base.h"
#include "shapes/polyline.h"

class PolylineDrawingTool : public AToolBase
{
    Q_OBJECT

public:
    PolylineDrawingTool(QObject *parent = 0);

    // Return the polyline constructed by this tool
    void getPolyline(APolyline &line);

    void paint(QPainter *painter, const QRectF &rect);

    void setStartPos(QPointF point) { start_pos_ = point; }
    bool addPoint(QPointF point);

    bool onMousePress(QMouseEvent *event, QPointF cursorPos);
    bool onMouseDoubleClick(QMouseEvent *event, QPointF cursorPos);

protected:
    // Callback functions
    void onReset(void);

    QPointF start_pos_;

    QList<QPointF> points_;

};

#endif // POLYLINE_TOOL_H

