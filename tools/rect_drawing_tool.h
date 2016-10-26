#ifndef RECT_DRAWING_TOOL_H
#define RECT_DRAWING_TOOL_H

#include "polyline_drawing_tool_base.h"

class RectDrawingTool : public PolylineDrawingToolBase
{
    Q_OBJECT

public:
    RectDrawingTool(QObject *parent = 0);

    bool addPoint(QPointF point);

    void paintTool(QPainter *painter, const QRectF &rect);
    void paintHints(QPainter *painter, const QRectF &rect);
};

#endif // RECT_DRAWING_TOOL_H

