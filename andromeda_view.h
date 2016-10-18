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

private:
};

#endif // ANDROMEDA_VIEW_H

