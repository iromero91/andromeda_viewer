#ifndef DRAWABLE_ENUMS_H
#define DRAWABLE_ENUMS_H

#include <stdint.h>

/**
 * @brief The DRAWABLE_KEY enum describes integer keys
 */
enum class DRAWABLE_KEY : int {

    // Used for storing the 'type' of the drawable item
    ITEM_TYPE = 0x100,

    // Used for storing the layer ID of the drawable item
    ITEM_LAYER = 0x200,
};

#endif // DRAWABLE_ENUMS_H

