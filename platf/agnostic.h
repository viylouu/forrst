#ifndef FUR_PLATFORM_AGNOSTIC_H
#define FUR_PLATFORM_AGNOSTIC_H

#include <core/macros.h>
#include <platf/glfw/main.h>



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
     * must be called after fur_platf_constr has been called
*** USAGE ***
...
fur_platf_constr(&state);
// window stuff
fur_platf_destr(&state);
*** ***** ***
     */
void fur_platf_destr(FUR_platfState* state);

    /* fur_platf_shouldWindowClose func
     * returns if the window should store processing events
     *
     * params
     * - FUR_platfState* state -- the input platform state
     *
     * must be called after fur_platf_constr has been called
     */
b8 fur_platf_shouldWindowClose(FUR_platfState* state);

    /* fur_platf_poll func
     * grabs input events
     *
     * params
     * - FUR_platfState* state -- the input platform state
     *
     * must be called after fur_platf_constr has been called
     */
void fur_platf_poll(FUR_platfState* state);

    /* fur_platf_present func
     * presents/swaps the current window's buffer
     *
     * params
     * - FUR_platfState* state -- the input platform state
     *
     * must be called after fur_platf_constr has been called
     */
void fur_platf_present(FUR_platfState* state);

#endif
