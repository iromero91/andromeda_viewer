#include "tool_base.h"

#include "layers/layer_defines.h"

AToolBase::AToolBase(QObject *parent) : QObject(parent)
{

}

void AToolBase::start()
{
    reset();

    onStart();

}

void AToolBase::stop()
{
    reset();

    tool_state_ = TOOL_STATE::INACTIVE;

    onStop();
}

void AToolBase::reset()
{
    tool_state_ = TOOL_STATE::RESET;

    onReset();

    // Let anyone watching know that the tool has updated
    emit updated();
}

void AToolBase::finish()
{
    onFinish();
    emit finished();
}

/**
 * @brief AToolBase::cancel
 * Cancel the tool
 */
void AToolBase::cancel()
{
    tool_state_ = TOOL_STATE::INACTIVE;

    reset();

    onCancel();

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

/* Event Passthrough Functions */
bool AToolBase::onMousePress(QMouseEvent *event, QPointF cursorPos)
{
    Q_UNUSED(event);
    Q_UNUSED(cursorPos);

    return false;
}

bool AToolBase::onMouseRelease(QMouseEvent *event, QPointF cursorPos)
{
    Q_UNUSED(event);
    Q_UNUSED(cursorPos);

    return false;
}

bool AToolBase::onMouseMove(QPointF cursorPos)
{
    tool_pos_ = cursorPos;

    return false;
}

bool AToolBase::onMouseDoubleClick(QMouseEvent *event, QPointF cursorPos)
{
    Q_UNUSED(event);
    Q_UNUSED(cursorPos);

    return false;
}

bool AToolBase::onKeyPress(QKeyEvent *event)
{
    Q_UNUSED(event);

    return false;
}

bool AToolBase::onKeyRelease(QKeyEvent *event)
{
    Q_UNUSED(event);

    return false;
}
