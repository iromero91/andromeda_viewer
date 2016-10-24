#include "drawing_tool_base.h"

#include "layers/layer_defines.h"

ADrawingTool::ADrawingTool() :
    QGraphicsObject(),
    tool_state_(0)
{
    clear();

    defaultPen();
    defaultBrush();

    setZValue((int) LAYER_ID::TOOLS);
}

/**
 * @brief ADrawingTool::clear
 * Reset the tool to a default state
 */
void ADrawingTool::clear()
{
    reset();
    setVisible(false);
}

/**
 * @brief ADrawingTool::update
 * Update the tool position (e.g. as the user moves the mouse around)
 * @param pos
 */
void ADrawingTool::update(QPointF pos)
{
    tool_pos_ = pos;

    onUpdate();
}

/**
 * @brief ADrawingTool::cancel
 * Cancel the tool
 */
void ADrawingTool::cancel()
{
    clear();
    emit cancelled();
}

// Set the default outline pen
void ADrawingTool::defaultPen()
{
    QPen pen(DRAWING_TOOL_OUTLINE_COLOR);

    pen.setWidthF(2);
    pen.setStyle(Qt::DashLine);
    pen.setCosmetic(true);

    setPen(pen);
}

// Set the default tool brush
void ADrawingTool::defaultBrush()
{
    QBrush brush(Qt::NoBrush);

    setBrush(brush);
}
