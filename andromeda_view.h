#ifndef ANDROMEDA_VIEW_H
#define ANDROMEDA_VIEW_H

#include <QGraphicsView>
#include <QMouseEvent>
#include <QWheelEvent>
#include <QKeyEvent>
#include <QPaintEvent>

#include "andromeda_scene.h"
#include "lwpolyline.h"

#define ANDROMEDA_VIEW_MAX_SCALING 100.0f
#define ANDROMEDA_VIEW_MIN_SCALING 0.001f

class AndromedaView : public QGraphicsView
{
    Q_OBJECT

public:
    AndromedaView(QWidget *parent = 0);

    void setScene(AndromedaScene *scene);
    AndromedaScene* getScene() { return scene_; }

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

    // Cursor functions
    void setCursorStyle(unsigned char style);
    unsigned char getCursorStyle() { return cursorStyle_; }

    /* View State Machine */
    enum AndromedaViewActions
    {
        VIEW_NO_ACTION = 0x00,

        VIEW_ACTION_SELECTING = 0x01,    // Drawing a selection rectangle
    };

    enum AndromedaViewFlags
    {
        VIEW_NO_FLAGS = 0x00,

        // Drawing flags
        VIEW_FLAG_DRAW_OVERLAY = 0x01,
    };

    enum AndromedaCursorStyles
    {
        VIEW_CURSOR_NONE = 0x00,    // No extra cursor is displayed
        VIEW_CURSOR_POINT,          // Draw a small point
        VIEW_CURSOR_CROSS_SMALL,    // Draw a small cross
        VIEW_CURSOR_CROSS_LARGE,    // Draw a large cross (to screen boundaries)

        VIEW_CURSOR_NUM_STYLES
    };

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
    void mouseDoubleClickEvent(QMouseEvent *event);

    void keyPressEvent(QKeyEvent *event);
    void paintEvent(QPaintEvent *event);

    // Painting functions (drawn in scene coordinates)
    //void drawBackground(QPainter *painter, const QRectF &rect);
    void drawForeground(QPainter *painter, const QRectF &rect);
    void drawSelectionMarquee(QPainter *painter, const QRectF &rect);

    // Overlay functions (drawn in viewport coordinates)
    void drawOverlay(QPainter *painter, QRect rect);
    void drawCursor(QPainter *painter, QRect rect);

    AndromedaScene *scene_;

    QPointF cursorPos_; // Current location of the cursor
    QPointF startPos_;  // Location of the 'starting' position (used for multiple functions)

    // Selection functions
    QRectF getSelectionMarquee();

    // State machine functions
    unsigned int viewAction_;    // View state machine (current action)
    void cancelViewAction() { viewAction_ = VIEW_NO_ACTION; }
    void setViewAction(unsigned int action, bool on = true);
    void clearViewAction(unsigned int action);
    bool checkViewAction(unsigned int action);



    unsigned char cursorStyle_;     // Cursor style

    unsigned int viewFlags_;    // View flags
    void setViewFlags(unsigned int flags, bool on = true);
    void clearViewFlags(unsigned int flags);
    bool checkViewFlags(unsigned int flags);

private:
};

#endif // ANDROMEDA_VIEW_H

