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

// Layer mask enumerations
enum class LAYER_MASK : uint64_t {

    // Mask for no layers
    NONE = 0x00,

    // Maks for all layers
    ALL = UINT64_MAX
};

// Generic layer enumerations
enum class LAYER_ID : unsigned char {
    NONE    = 0,

    // The currently selected layer is forced to the top
    SELECTED = 62,
};

// PCB layer enumeration
enum class PCB_LAYER_ID : unsigned char {
    // Layers that sit behind the copper layer
    BOARD_OUTLINE       =  1,    //!< Outline layer defines the shape of the PCB
    BOARD_MARGINS       =  2,    //!< Defines global margins

    // Back Layers
    BACK_FABRICATION    =  8,
    BACK_MECHANICAL     =  9,
    BACK_COURTYARD      = 10,
    BACK_SILKSCREEN     = 11,
    BACK_ADHESIVE       = 12,
    BACK_PASTE          = 13,
    BACK_MASK           = 14,
    BACK_COPPER         = 15,

    // Internal copper layers
    INTERNAL_COPPER_1	= 16,
    INTERNAL_COPPER_2,
    INTERNAL_COPPER_3,
    INTERNAL_COPPER_4,
    INTERNAL_COPPER_5,
    INTERNAL_COPPER_6,
    INTERNAL_COPPER_7,
    INTERNAL_COPPER_8,
    INTERNAL_COPPER_9,
    INTERNAL_COPPER_10,
    INTERNAL_COPPER_11,
    INTERNAL_COPPER_12,
    INTERNAL_COPPER_13,
    INTERNAL_COPPER_14,
    INTERNAL_COPPER_15,
    INTERNAL_COPPER_16,
    INTERNAL_COPPER_17,
    INTERNAL_COPPER_18,
    INTERNAL_COPPER_19,
    INTERNAL_COPPER_20,
    INTERNAL_COPPER_21,
    INTERNAL_COPPER_22,
    INTERNAL_COPPER_23,
    INTERNAL_COPPER_24,
    INTERNAL_COPPER_25,
    INTERNAL_COPPER_26,
    INTERNAL_COPPER_27,
    INTERNAL_COPPER_28,
    INTERNAL_COPPER_29,
    INTERNAL_COPPER_30,
    INTERNAL_COPPER_31,
    INTERNAL_COPPER_32,

    // Front Layers
    FRONT_COPPER        = 48,
    FRONT_MASK          = 49,
    FRONT_PASTE         = 50,
    FRONT_SILKSCREEN    = 51,
    FRONT_ADHESIVE      = 52,
    FRONT_COURTYARD     = 53,
    FRONT_MECHANICAL    = 54,
    FRONT_FABRICATION   = 55,  //!< Component outline and placement markers

    DRAWINGS            = 56,  //!< Reserved for user drawings
    COMMENTS            = 57,  //!< Reserved for user comments

    USER_A              = 58,
    USER_B              = 59,
    USER_C              = 60,
};

/* Layer Masks */
const uint64_t PCB_LAYER_MASK_BACK   = ((uint64_t) 0xFF) << (int) PCB_LAYER_ID::BACK_FABRICATION;
const uint64_t PCB_LAYER_MASK_FRONT  = ((uint64_t) 0xFF) << (int) PCB_LAYER_ID::FRONT_COPPER;
const uint64_t PCB_LAYER_MASK_INTERNAL_COPPER = (uint64_t) 0xFFFFFFFF << (int) PCB_LAYER_ID::INTERNAL_COPPER_1;
const uint64_t PCB_LAYER_MASK_ALL_COPPER = ((uint64_t) PCB_LAYER_MASK_INTERNAL_COPPER) | ((uint64_t) 1 << (int) PCB_LAYER_ID::BACK_COPPER) | ((uint64_t) 1 << (int) PCB_LAYER_ID::FRONT_COPPER);

uint64_t LayerIdToMask(unsigned char layerId);

#endif // LAYER_DEFINITIONS_H

