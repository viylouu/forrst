#ifndef FST_MACROS_H
#define FST_MACROS_H

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef int8_t s8;
typedef int16_t s16;
typedef int32_t s32;
typedef int64_t s64;
typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;
typedef intptr_t sptr;
typedef uintptr_t uptr;
typedef float f32;
typedef double f64;
typedef u8 b8;
typedef u16 b16;
typedef u32 b32;
typedef u64 b64;

typedef struct { f32 x; f32 y; } v2;
typedef struct { f32 x; f32 y; f32 z; } v3;
typedef struct { f32 x; f32 y; f32 z; f32 w; } v4;

#define UNUSED(param) \
    (void)(param)

#define ERROR_IF(check, print) do { \
    if((check)) { \
        printf(print); \
        exit(1); \
    } \
} while(0)

#define MAYBE_CALL(func, ...) \
    if ((func)) func(__VA_ARGS__)

#endif
