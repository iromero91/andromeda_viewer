#ifndef ANDROMEDA_VIEW_H
#define ANDROMEDA_VIEW_H

#include <QGraphicsView>
#include <QMouseEvent>
#include <QWheelEvent>
#include <QKeyEvent>
#include <QPaintEvent>

#include "andromeda_scene.h"

#define ANDROMEDA_VIEW_MAX_SCALING 100.0f
#define ANDROMEDA_VIEW_MIN_SCALING 0.001f

class AndromedaView : public QGraphicsView
{
    Q_OBJECT

public:
    AndromedaView(QWidget *parent = 0);

    void setScene(AndromedaScene *scene);
    AndromedaScene* getScene() { return scene_; }

    // Configuration flags
    void setOverlayEnabled(bool en) { drawOverlay_ = en; }
    bool getOverlayEnabled() { return drawOverlay_; }
    void setCursorEnabled(bool en) { drawCursor_ = en; }
    bool getCursorEnabled() { return drawCursor_; }

    // Viewport functions
    QPointF getCenterLocation();
    QRectF getViewport();
    QPointF unitsPerPixel();

    QPointF getCursorPos() { return cursorPos_; }
    void setCursorPos(QPointF pos);
    void moveCursor(QPointF offset);
    void moveCursor(double dx, double dy);

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

    bool drawOverlay_;
    bool drawCursor_;

    AndromedaScene *scene_;

    QPointF cursorPos_;

private:
};

#endif // ANDROMEDA_VIEW_H

