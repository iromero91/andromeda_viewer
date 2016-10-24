#include "tool_base.h"

#include "layers/layer_defines.h"

AToolBase::AToolBase() :
    QGraphicsObject(),
    tool_state_(0)
{
    setZValue((int) LAYER_ID::TOOLS);
    setVisible(false);
}

/**
 * @brief AToolBase::clear
 * Reset the tool to a default state
 */
void AToolBase::clear()
{
    reset();
    setVisible(false);
}

/**
 * @brief AToolBase::update
 * Update the tool position (e.g. as the user moves the mouse around)
 * @param pos
 */
void AToolBase::update(QPointF pos)
{
    tool_pos_ = pos;

    onUpdate();

    prepareGeometryChange();
}

void AToolBase::onUpdate()
{
    // Reimplement this as a callback
}

/**
 * @brief AToolBase::cancel
 * Cancel the tool
 */
void AToolBase::cancel()
{
    clear();
    emit cancelled();
}
