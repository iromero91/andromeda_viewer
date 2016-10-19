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

    // Cursor functions
    QPointF getCursorPos() { return cursorPos_; }
    void setCursorPos(QPointF pos, bool panPastEdges = false);
    void moveCursor(QPointF offset, bool panPastEdges = false);
    void moveCursor(double dx, double dy, bool panPastEdges = false);
    void snapMouseToCursor();

    void scroll(QPoint offset);
    void scroll(int dx, int dy);

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

    void keyPressEvent(QKeyEvent *event);
    void paintEvent(QPaintEvent *event);

    // Painting functions (drawn in scene coordinates)
    void drawForeground(QPainter *painter, const QRectF &rect);
    void drawSelectionMarquee(QPainter *painter, const QRectF &rect);

    // Overlay functions (drawn in viewport coordinates)
    void drawOverlay(QPainter *painter, QRect rect);
    void drawCursor(QPainter *painter, QRect rect);

    bool drawOverlay_;
    bool drawCursor_;

    AndromedaScene *scene_;

    QPointF cursorPos_;

    // Selection functions
    bool selectionActive_;  // True if user is drawing a selection cursor
    QPointF selectionStartPos_; // Location (in scene coords) of the start of the select rect
    QRectF getSelectionRect();

private:
};

#endif // ANDROMEDA_VIEW_H

