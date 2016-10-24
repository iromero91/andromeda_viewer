#ifndef ANDROMEDA_VIEW_H
#define ANDROMEDA_VIEW_H

#include <QGraphicsView>
#include <QMouseEvent>
#include <QWheelEvent>
#include <QKeyEvent>
#include <QPaintEvent>
#include <QCursor>

#include "andromeda_scene.h"
#include "tools/tool_base.h"

#define ANDROMEDA_VIEW_MAX_SCALING 100.0f
#define ANDROMEDA_VIEW_MIN_SCALING 0.001f

class AView : public QGraphicsView
{
    Q_OBJECT

public:
    AView(QWidget *parent = 0);

    void setScene(AScene *scene);
    AScene* getScene(void) { return scene_; }

    // Viewport functions
    QPointF getCenterLocation(void);
    QRectF getViewport(void);
    QPointF unitsPerPixel(void);

    // Cursor functions
    QPointF getCursorPos(void) { return cursorPos_; }
    QPointF getCursorOrigin(void) { return cursorOrigin_; }
    void setCursorPos(QPointF pos, bool panPastEdges = false);
    void moveCursor(QPointF offset, bool panPastEdges = false);
    void moveCursor(double dx, double dy, bool panPastEdges = false);
    void snapMouseToCursor(void);
    void setCursorStyle(unsigned char style);
    unsigned char getCursorStyle(void) { return cursorStyle_; }

    void scroll(QPoint offset);
    void scroll(int dx, int dy);

    // View scaling functions
    double getScalingFactor(void) { return transform().m11(); }
    void setScalingFactor(double scaling);
    void scaleRelative(double scaling);

    // Item deletion
    void deleteItems(QList<QGraphicsItem*> items);
    void deleteSelectedItems(void);

    // Tool functions
    bool startTool(void);           // Start the current tool
    bool startTool(AToolBase *tool);
    void cancelTool(void);
    bool isToolActive(void);
    bool isToolAvailable() { return current_tool_ != nullptr; }

    enum AViewFlags
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

protected:
    // UI event callbacks
    void wheelEvent(QWheelEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseDoubleClickEvent(QMouseEvent *event);

    void keyPressEvent(QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent *event);

    void paintEvent(QPaintEvent *event);

    // Painting functions (drawn in scene coordinates)
    //void drawBackground(QPainter *painter, const QRectF &rect);
    void drawForeground(QPainter *painter, const QRectF &rect);
    void drawSelectionMarquee(QPainter *painter, const QRectF &rect);

    // Overlay functions (drawn in viewport coordinates)
    void drawOverlay(QPainter *painter, QRect rect);
    void drawCursor(QPainter *painter, QRect rect);

    AScene *scene_;

    QPointF cursorOrigin_;  // 'Origin' of the cursor
    QPointF cursorPos_; // Current location of the cursor
    QPointF startPos_;  // Location of the 'starting' position (used for multiple functions)

    // Selection functions
    QRectF getSelectionMarquee(void);

    // Tools
    AToolBase *current_tool_;

    unsigned char cursorStyle_;     // Cursor style

    unsigned int viewFlags_;    // View flags

    // Mouse panning
    bool mouse_pan_active_;
    void startMousePan();
    void endMousePan();

    // Selection
    bool selection_active_;
    void startSelection();
    void finishSelection();
    void cancelSelection();

private:
};

#endif // ANDROMEDA_VIEW_H

