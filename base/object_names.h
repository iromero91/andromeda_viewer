#ifndef OBJECT_NAMES_H
#define OBJECT_NAMES_H

namespace OBJECT_NAME
{
// Base object class
const QString A_OBJECT = "AndromedaObject";

// Drawable base
const QString A_DRAWABLE_BASE = "ADrawableBase";

// Drawable primitives
const QString A_DRAWABLE_PRIMITIVE = "ADrawablePrimitive";
const QString A_DRAWABLE_ELLIPSE = "ADrawableEllipse";
const QString A_DRAWABLE_POLYLINE = "ADrawablePolyline";
const QString A_DRAWABLE_SYMBOL_PIN = "ADrawabableSymbolPin";
}

namespace TOOL_NAME
{
const QString BASE = "ToolBase";

// Primitive drawing tools
const QString DRAW_POLYLINE = "DrawPolyline";
const QString DRAW_ELLIPSE = "DrawEllipse";
const QString DRAW_RECT = "DrawRect";

// Primitive edit tools
const QString EDIT_POLYLINE = "EditPolyline";
}

#endif // OBJECT_NAMES_H

