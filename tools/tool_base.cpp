#include "tool_base.h"

#include "layers/layer_defines.h"

AToolBase::AToolBase() : QObject()
{
}

/**
 * @brief AToolBase::clear
 * Reset the tool to a default state
 */
void AToolBase::clear()
{
    reset();
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

/**
 * @brief AToolBase::paint
 * Paint the tool on top of the scene
 * @param painter
 */
void AToolBase::paint(QPainter *painter, const QRectF &rect)
{
    // Reimplement in specific tool class
    Q_UNUSED(painter);
    Q_UNUSED(rect);
}
