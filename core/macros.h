#ifndef FUR_MACROS_H
#define FUR_MACROS_H

/* ====== TYPES ====== */

/* --- INTEGERS --- */
typedef signed char s8;
typedef short       s16;
typedef int         s32;
typedef long long   s64;
/* --- UNSIGNED INTEGERS --- */
typedef unsigned char      u8;
typedef unsigned short     u16;
typedef unsigned int       u32;
typedef unsigned long long u64;
/* --- FLOATS --- */
typedef float  f32;
typedef double f64;
/* --- BOOLEANS --- */
typedef u8  b8;
typedef u16 b16;
typedef u32 b32;
typedef u64 b64;

/* ====== ERRORS AND WARNINGS ====== */

    /* ERROR macro
     * sends an error message to the console, extra text provided by user
     * then quits the program
     */
#define ERROR(...) do { \
        printf("ERROR! [\"%s\" ln:%d]\n", __FILE__, __LINE__); \
        printf(__VA_ARGS__); \
        exit(1); \
    } while (0)

    /* WARN macro
     * sends a warning message to the console, extra text provided by user
     */
#define WARN(...) do { \
        printf("WARNING! [\"%s\" ln:%d]\n", __FILE__, __LINE__); \
        printf(__VA_ARGS__;; \
    } while (0)

    /* WARN_RET macro
     * sends a warning message to the console, extra text provided by user
     * then returns a value
     * > useful for easy function returns
     */
#define WARN_RET(val, ...) \
    WARN(__VA_ARGS__); \
    return val

/* ====== VARIABLE STUFF ====== */

#define NEW(type) \
    malloc(sizeof(type))

#endif
