#ifndef LAYER_DEFINITIONS_H
#define LAYER_DEFINITIONS_H

#include <stdint.h>

// Layer display modes
enum class LAYER_MODE : uint8_t {

    // Show *no* layers
    SHOW_NONE = 0x00,

    // Show the selected layer - all other layers are greyed out
    HIGHLIGHT,

    // Show the selected layer - all other layers are invisible
    HIDDEN,

    // Display *all* layers
    SHOW_ALL = 0xFF,
};

// Layer enumerations
enum class LAYER : uint64_t {

    // Mask for no layers
    NONE = 0x00,

    // Mask for all layers
    ALL = UINT64_MAX
};

#endif // LAYER_DEFINITIONS_H

