#include "layer_definitions.h"

uint64_t LayerIdToMask(unsigned char layerId)
{
    if (layerId > 63) layerId = 0;

     return (uint64_t) 1 << layerId;
}
