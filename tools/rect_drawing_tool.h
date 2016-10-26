#ifndef RECT_DRAWING_TOOL_H
#define RECT_DRAWING_TOOL_H

#include "polyline_drawing_tool.h"

class RectDrawingTool : public PolylineToolBase
{
    Q_OBJECT

public:
    RectDrawingTool(QObject *parent = 0);

    bool addPoint(QPointF point);

    APolyline* getPolyline(void);

    void paintTool(QPainter *painter, const QRectF &rect);

    QRectF getRect(void);
};

#endif // RECT_DRAWING_TOOL_H

