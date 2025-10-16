#ifndef FUR_PLATFORM_AGNOSTIC_H
#define FUR_PLATFORM_AGNOSTIC_H

#include <platf/glfw/main.h>

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

/* ====== FUNCS ====== */

    /* fur_platf_constr func
     * constructs the input platform state
     *
     * params:
     * - FUR_platfState* state -- the input platform state
     *
     * input platform state must be created manually
*** USAGE ***
FUR_platfState* state = NEW(FUR_platfState);
state->plat = ...
state->title = ...
state->width = ...
...
fur_platf_constr(state);
// do stuff
*** ***** ***
     */
void fur_platf_constr(FUR_platfState* state);

    /* fur_platf_destr func
     * destructs the input platform state
     *
     * params
     * - FUR_platfState* state -- the input platform state
     *
     * input platform state must be created manually
     * must be called after fur_platf_constr has been called
*** USAGE ***
FUR_platfState* state = NEW(FUR_platfState);
state->plat = ...
state->title = ...
state->width = ...
...
fur_platf_constr(&state);
// do something
fur_platf_destr(&state);
*** ***** ***
     */
void fur_platf_destr(FUR_platfState* state);

#endif
