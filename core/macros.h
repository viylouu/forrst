#ifndef FST_MACROS_H
#define FST_MACROS_H

#include <stdio.h>
#include <stdlib.h>

typedef signed char s8;
typedef short s16;
typedef int s32;
typedef long long s64;
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef unsigned long long u64;
typedef float f32;
typedef double f64;
typedef u8 b8;
typedef u16 b16;
typedef u32 b32;
typedef u64 b64;

#define UNUSED(param) \
    (void)(param)

#define ERROR_IF(check, print) do { \
    if((check)) { \
        printf(print); \
        exit(1); \
    } \
} while(0)

#endif
