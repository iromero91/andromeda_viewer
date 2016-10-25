#include "tool_base.h"

#include "layers/layer_defines.h"

AToolBase::AToolBase(QObject *parent) : QObject(parent)
{
    defaultPens();
}

void AToolBase::defaultPens()
{
    // Fill brush
    tool_brush_ = QBrush(Qt::NoBrush);

    // Pen for tool outline
    tool_pen_.setColor(DRAWING_TOOL_OUTLINE_COLOR);
    tool_pen_.setWidthF(2.5);
    tool_pen_.setCosmetic(true);
    tool_pen_.setStyle(Qt::DashDotLine);

    trace_pen_.setColor(DRAWING_TOOL_TRACE_LINE_COLOR);
    trace_pen_.setWidthF(2.0);
    trace_pen_.setCosmetic(true);
    trace_pen_.setStyle(Qt::DotLine);
}

void AToolBase::start()
{
    reset();

    onStart();
}

void AToolBase::reset()
{
    setToolState(TOOL_STATE::RESET);

    onReset();

    // Let anyone watching know that the tool has updated
    emit updated();
}

void AToolBase::finish()
{
    setToolState(TOOL_STATE::FINISHED);
    onFinish();
    emit finished();
}

/**
 * @brief AToolBase::cancel
 * Cancel the tool
 */
void AToolBase::cancel()
{
    reset();

    setToolState(TOOL_STATE::INACTIVE);

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
