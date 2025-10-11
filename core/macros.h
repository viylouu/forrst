#ifndef FUR_MACROS_H
#define FUR_MACROS_H

#ifdef __cplusplus
extern "C" {
#endif

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

#define ERROR_IF(check, ...) do {                           \
    if((check)) {                                           \
        printf("ERROR! \"%s\" [%d]\n", __FILE__,__LINE__);  \
        printf(__VA_ARGS__);                                \
        printf("\n\ni am become death\ndestroyer of terminals\n⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡿⠿⠿⠿⠿⢿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿\n\
⣿⣿⣿⣿⣿⣿⣿⣿⠟⠋⠁⠀⠀⠀⠀⠀⠀⠀⠀⠉⠻⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿\n\
⣿⣿⣿⣿⣿⣿⣿⠁⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢺⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿\n\
⣿⣿⣿⣿⣿⣿⣿⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠆⠜⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿\n\
⣿⣿⣿⣿⠿⠿⠛⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠉⠻⣿⣿⣿⣿⣿\n\
⣿⣿⡏⠁⠀⠀⠀⠀⠀⣀⣠⣤⣤⣶⣶⣶⣶⣶⣦⣤⡄⠀⠀⠀⠀⢀⣴⣿⣿⣿⣿⣿\n\
⣿⣿⣷⣄⠀⠀⠀⢠⣾⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⢿⡧⠇⢀⣤⣶⣿⣿⣿⣿⣿⣿⣿\n\
⣿⣿⣿⣿⣿⣿⣾⣮⣭⣿⡻⣽⣒⠀⣤⣜⣭⠐⢐⣒⠢⢰⢸⣿⣿⣿⣿⣿⣿⣿⣿⣿\n\
⣿⣿⣿⣿⣿⣿⣿⣏⣿⣿⣿⣿⣿⣿⡟⣾⣿⠂⢈⢿⣷⣞⣸⣿⣿⣿⣿⣿⣿⣿⣿⣿\n\
⣿⣿⣿⣿⣿⣿⣿⣿⣽⣿⣿⣷⣶⣾⡿⠿⣿⠗⠈⢻⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿\n\
⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡿⠻⠋⠉⠑⠀⠀⢘⢻⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿\n\
⣿⣿⣿⣿⣿⣿⣿⡿⠟⢹⣿⣿⡇⢀⣶⣶⠴⠶⠀⠀⢽⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿\n\
⣿⣿⣿⣿⣿⣿⡿⠀⠀⢸⣿⣿⠀⠀⠣⠀⠀⠀⠀⠀⡟⢿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿\n\
⣿⣿⣿⡿⠟⠋⠀⠀⠀⠀⠹⣿⣧⣀⠀⠀⠀⠀⡀⣴⠁⢘⡙⢿⣿⣿⣿⣿⣿⣿⣿⣿\n\
⠉⠉⠁⠀⠀⠀⠀⠀⠀⠀⠀⠈⠙⢿⠗⠂⠄⠀⣴⡟⠀⠀⡃⠀⠉⠉⠟⡿⣿⣿⣿⣿\n\
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢷⠾⠛⠂⢹⠀⠀⠀⢡⠀⠀⠀⠀⠀⠙⠛⠿⢿\n");\
        exit(1);                                            \
    } \
} while(0)

#define RETURN_IF(check, val, ...) do {                     \
        if((check)) {                                       \
        printf("ERROR! \"%s\" [%d]\n", __FILE__,__LINE__);  \
        printf(__VA_ARGS__);                                \
        return val;                                         \
    } \
} while(0)


#define MAYBE_CALL(func, ...) \
    if ((func)) func(__VA_ARGS__)

#define FUR_OPS1(a) ops a
#define FUR_OPS2(a,b) ops a; ops b
#define FUR_OPS3(a,b,c) ops a; ops b; ops c
#define FUR_OPS4(a,b,c,d) ops a; ops b; ops c; ops d
#define FUR_OPS5(a,b,c,d,e) ops a; ops b; ops c; ops d; ops e

#define FUR_OPS_GET(_1,_2,_3,_4,_5,NAME,...) NAME
#define FUR_OPS_HELPER(...) \
    FUR_OPS_GET(__VA_ARGS__, FUR_OPS5,FUR_OPS4,FUR_OPS3,FUR_OPS2,FUR_OPS1)(__VA_ARGS__)

#ifdef __cplusplus
}
#endif

#endif
