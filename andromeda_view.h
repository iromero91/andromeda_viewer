#ifndef ANDROMEDA_VIEW_H
#define ANDROMEDA_VIEW_H

#include <QGraphicsView>
#include <QMouseEvent>
#include <QWheelEvent>
#include <QKeyEvent>
#include <QPaintEvent>

#define ANDROMEDA_VIEW_MAX_SCALING 100.0f
#define ANDROMEDA_VIEW_MIN_SCALING 0.001f

class AndromedaView : public QGraphicsView
{
    Q_OBJECT

public:
    AndromedaView(QWidget *parent = 0);

    // Configuration flags
    void setOverlayEnabled(bool en) { draw_overlay_ = en; }
    bool getOverlayEnabled() { return draw_overlay_; }
    void setCursorEnabled(bool en) { draw_cursor_ = en; }
    bool getCursorEnabled() { return draw_cursor_; }

    // Viewport functions
    QPointF getCenterLocation();
    QRectF getViewport();

    // View scaling functions
    double getScalingFactor() { return transform().m11(); }
    void setScalingFactor(double scaling);
    void scaleRelative(double scaling);

public slots:

signals:
    // Called when the user cursor changes (in scene coordinates)
    void cursorPositionChanged(QPointF pos);

protected:
    // UI event callbacks
    void wheelEvent(QWheelEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);

    void paintEvent(QPaintEvent *event);

    // Overlay functions
    void drawOverlay(QPainter *painter, QRect rect);
    void drawCursor(QPainter *painter, QRect rect);

    bool draw_overlay_;
    bool draw_cursor_;

private:
};

#endif // ANDROMEDA_VIEW_H

