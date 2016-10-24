#ifndef TOOL_DEFINES_H
#define TOOL_DEFINES_H

#include <QColor>

// Color of tool outline
const QColor DRAWING_TOOL_OUTLINE_COLOR(125,200,250,200);

// Color of line between last point and mouse
const QColor DRAWING_TOOL_TRACE_LINE_COLOR(225,250,250,200);

enum class TOOL_STATE : int {
    INACTIVE = 0,
};

#endif // TOOL_DEFINES_H

