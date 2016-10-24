#include "tool_base.h"

#include "layers/layer_defines.h"

AToolBase::AToolBase() :
    QGraphicsObject(),
    tool_state_((int) TOOL_STATE::INACTIVE)
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
 * @brief AToolBase::cancel
 * Cancel the tool
 */
void AToolBase::cancel()
{
    tool_state_ = (int) TOOL_STATE::INACTIVE;
    clear();
    emit cancelled();
}
