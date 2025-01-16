#pragma once

typedef signed char        int8,  sint8;
typedef signed short int   int16, sint16;
typedef signed int         int32, sint32;
typedef signed long long   int64, sint64;

typedef unsigned char      uint8;
typedef unsigned short int uint16;
typedef unsigned int       uint32;
typedef unsigned long long uint64;

// Color has no 32-bit support, so int types (_t'd ones) are always 64-bit (ssize_t and size_t)
// Color's sint_t is equivalent to ssize_t and Color's uint_t is equivalent to size_t.
// The reason this convention is used is that it's the standard and we might add 32-bit support in the future.
// --------------------------------------------------------------------------------------------------------------

typedef int64  sint_t;
typedef uint64 uint_t;
