#include <stdint.h>
#include "hash-djb2.h"
#include "io.h"
#include "malloc.h"
#include "type.h"

uint32_t hash_djb2(const uint8_t * str, ssize_t _max)
{
    uint32_t hash = 5381;
    uint8_t c;
    uint32_t max = (uint32_t) _max;
    while (((c = *str++)) && max--) {
        hash = ((hash << 5) + hash) ^ c;
    }

    return hash;
}
