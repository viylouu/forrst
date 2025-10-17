#ifndef FUR_PLATFORM_STATE_H
#define FUR_PLATFORM_STATE_H

// this is just for platforms to be able to access FUR_platfState in their datatypes

#include <core/macros.h>

/* ====== DATATYPES ====== */

    /* FUR_target_platfState union
     * pointer to the underlying os/platform specific data
     * (not a pointer because i like typing TYPE*)
     * valid cases:
     * - FUR_glfw_platfState
     */
typedef void FUR_target_platfState;

    /* FUR_targetPlatf enum
     */
typedef enum {
    FUR_PLATF_GLFW
} FUR_targetPlatf;

    /* FUR_platfState struct
     * holds the os/platform agnostic data
     * aswell as the specific data (stored as a FUR_target_platfState)
     */
typedef struct {
    FUR_target_platfState* spec;
    FUR_targetPlatf plat;

    char* title;
    s32 width, height;
} FUR_platfState;

#endif
