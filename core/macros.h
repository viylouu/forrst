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

#define ERROR(...) do { \
        printf("ERROR! [\"%s\" ln:%d]\n", __FILE__, __LINE__); \
        printf(__VA_ARGS__); \
        exit(1); \
    } while (0)

#define ERROR_IF(cond,...) do { if ((cond)) { ERROR(__VA_ARGS__); } } while(0)

#define WARN(...) do { \
        printf("WARNING! [\"%s\" ln:%d]\n", __FILE__, __LINE__); \
        printf(__VA_ARGS__); \
    } while (0)

#define WARN_IF(cond,...) do { if ((cond)) { WARN(__VA_ARGS__); } } while(0)

#define WARN_RET(val, ...) \
    WARN(__VA_ARGS__); \
    return val

/* ====== VARIABLE STUFF ====== */

#define NEW(type) \
    malloc(sizeof(type))

/* ====== API SPECIFIERS ====== */

#define crit_def_for(func) default: ERROR("selected api has no support for function \"%s\"!\n", func); break
#define warn_def_for(func) default: WARN ("selected api has no support for function \"%s\"!\n", func); break

#endif
