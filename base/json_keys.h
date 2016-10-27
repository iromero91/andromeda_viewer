#ifndef JSON_KEYS_H
#define JSON_KEYS_H

#include <QString>

/**
 * "Enumerated" keys for JSON reading / writing
 * It is safer to pass const values than continually re-type strings manually
 *
 */
namespace JSON_KEY {

// Item options
const QString ITEM_LAYER = "layer";

// Graphics options
const QString FILLED = "filled";


// Dimensions
const QString RADIUS = "radius";
const QString RADIUS_X = "rx";
const QString RADIUS_Y = "ry";
const QString POS_X = "x";
const QString POS_Y = "y";
const QString WIDTH = "width";
const QString HEIGHT = "height";
const QString THICKNESS = "thickness";

// Angles
const QString ANGLE = "angle";
const QString ROTATION = "rotation";

}

#endif // JSON_KEYS_H

