#ifndef FUR_MACROS_H
#define FUR_MACROS_H

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

#define ERROR(...) do { \
        printf("ERROR! [\"%s\" ln:%d]\n", __FILE__, __LINE__); \
        printf(__VA_ARGS__;; \
        exit(1); \
    } while (0)

#define WARN(...) do { \
        printf("WARNING! [\"%s\" ln:%d]\n", __FILE__, __LINE__); \
        printf(__VA_ARGS__;; \
    } while (0)

#define WARN_RET(val, ...) \
    WARN(__VA_ARGS__); \
    return val

#endif
