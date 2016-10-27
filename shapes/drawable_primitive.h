#ifndef DRAWABLE_PRIMITIVE_H
#define DRAWABLE_PRIMITIVE_H

#include "drawable_base.h"

#include <QColor>

class ADrawablePrimitive : public ADrawableBase
{
    Q_OBJECT

public:
    ADrawablePrimitive(QObject *parent = 0);

    Q_PROPERTY( bool filled READ filled WRITE setFilled )
    Q_PROPERTY( double lineWidth READ lineWidth WRITE setLineWidth )
    Q_PROPERTY( QColor fillColor READ fillColor WRITE setFillColor )
    Q_PROPERTY( QColor lineColor READ lineColor WRITE setLineColor )

    // Property getters
    bool filled(void) { return filled_; }
    double lineWidth(void) { return line_width_; }
    QColor fillColor(void) { return fill_color_; }
    QColor lineColor(void) { return line_color_; }
    Qt::PenStyle lineStyle(void) { return line_style_; }

public slots:
    void setFilled(bool filled) { filled_ = filled; }
    void setLineWidth(double lineWidth);
    void setLineStyle(Qt::PenStyle lineStyle) { line_style_ = lineStyle; }
    void setFillColor(QColor fillColor) { fill_color_ = fillColor; }
    void setLineColor(QColor lineColor) { line_color_ = lineColor; }

protected:
    // Properties unique to ADrawablePrimitive
    bool filled_        = true;
    double line_width_  = SYMBOL_LINE_WIDTH_DEFAULT;
    QColor fill_color_  = SYMBOL_FILL_COLOR;
    QColor line_color_  = SYMBOL_LINE_COLOR;
    Qt::PenStyle line_style_ = Qt::SolidLine;

    QPen pen(const QStyleOptionGraphicsItem *option = nullptr);
    QBrush brush(const QStyleOptionGraphicsItem *option = nullptr);
};

#endif // DRAWABLE_PRIMITIVE_H

