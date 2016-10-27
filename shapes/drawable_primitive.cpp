#include "drawable_primitive.h"

ADrawablePrimitive::ADrawablePrimitive(QObject *parent) : ADrawableBase(parent)
{
    setObjectName("ADrawablePrimitive");

    setFlags(ItemIsSelectable | ItemIsFocusable);
    setAcceptHoverEvents(true);
}

void ADrawablePrimitive::setLineWidth(double lineWidth)
{
    lineWidth = qMax(lineWidth, SYMBOL_LINE_WIDTH_MIN);

    //TODO - more logic needed perhaps?

    line_width_ = lineWidth;
}

QPen ADrawablePrimitive::pen(const QStyleOptionGraphicsItem *option)
{
    QColor color = line_color_;

    if ((nullptr != option) &&
        (option->state & QStyle::State_MouseOver))
    {
        color = color.light();
    }
    else if (isSelected())
    {
        color = color.dark();
    }

    QPen pen(color);
    pen.setWidthF(line_width_);
    pen.setStyle(line_style_);
    pen.setCapStyle(Qt::RoundCap);
    pen.setJoinStyle(Qt::RoundJoin);

    return pen;
}

QBrush ADrawablePrimitive::brush(const QStyleOptionGraphicsItem *option)
{
    if (!filled())
    {
        return QBrush(Qt::NoBrush);
    }

    QColor color = fill_color_;

    if ((nullptr != option) &&
        (option->state & QStyle::State_MouseOver))
    {
        color = color.light();
    }
    else if (isSelected())
    {
        color = color.dark();
    }

    QBrush b(color);

    //TODO anything else?

    return b;
}
