// test with (O32_HOST_ORDER == O32_LITTLE_ENDIAN)
// tests already written, but this could be the basis of a way to test all apps and packages as needed
// SOURCE: https://stackoverflow.com/questions/2100331/c-macro-definition-to-determine-big-endian-or-little-endian-machine
#ifndef ORDER32_H
#define ORDER32_H

#include <limits.h>
#include <stdint.h>

#if CHAR_BIT != 8
#error "unsupported char size"
#endif

enum
{
    O32_LITTLE_ENDIAN = 0x03020100ul,
    O32_BIG_ENDIAN = 0x00010203ul,
    O32_PDP_ENDIAN = 0x01000302ul
};

static const union { unsigned char bytes[4]; uint32_t value; } o32_host_order =
    { { 0, 1, 2, 3 } };

#define O32_HOST_ORDER (o32_host_order.value)

#endif
