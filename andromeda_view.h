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

    // Item deletion
    void deleteItems(QList<QGraphicsItem*> items);
    void deleteSelectedItems();

    /* View State Machine */
    enum AndromedaViewActions
    {
        VIEW_NO_ACTION = 0x00,

        VIEW_ACTION_SELECTING = 0x01,    // Drawing a selection rectangle
    };

    // Action functions
    unsigned int getAction();
    QList<unsigned int> getActionStack() { return actionStack_; }
    bool pushAction(unsigned int action, bool allowDuplicates = false);
    bool popAction();
    bool popAction(unsigned int action);
    void clearActions();

    enum AndromedaViewFlags
    {
        VIEW_NO_FLAGS = 0x00,

        // Drawing flags
        VIEW_FLAG_DRAW_OVERLAY = 0x01,
    };

    void setViewFlags(unsigned int flags, bool on = true);
    void clearViewFlags(unsigned int flags);
    bool checkViewFlags(unsigned int flags);

    enum AndromedaCursorStyles
    {
        VIEW_CURSOR_NONE = 0x00,    // No extra cursor is displayed
        VIEW_CURSOR_CROSS_SMALL,    // Draw a small cross
        VIEW_CURSOR_CROSS_LARGE,    // Draw a large cross (to screen boundaries)

        VIEW_CURSOR_NUM_STYLES
    };

public slots:

signals:
    // Called when the user cursor changes (in scene coordinates)
    void cursorPositionChanged(QPointF pos);
    void actionAdded(unsigned int action);
    void actionCancelled(unsigned int action);

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

    QList<unsigned int> actionStack_;
    virtual void onActionAdded(unsigned int action) = 0;
    virtual void onActionCancelled(unsigned int action) = 0;

    unsigned char cursorStyle_;     // Cursor style

    unsigned int viewFlags_;    // View flags


private:
};

#endif // ANDROMEDA_VIEW_H

