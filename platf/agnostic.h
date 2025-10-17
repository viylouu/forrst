#ifndef FUR_PLATFORM_AGNOSTIC_H
#define FUR_PLATFORM_AGNOSTIC_H

#include <core/macros.h>
#include <platf/state.h>

/* ====== FUNCS ====== */

    /* fur_platf_constr func
     * constructs the input platform state
     *
     * state requires:
     *  - title must be set
     *  - width must be set
     *  - height must be set
     *  - plat must be set
     *
     * params:
     * - FUR_platfState* state -- the input platform state
     */
void fur_platf_constr(FUR_platfState* state);

    /* fur_platf_destr func
     * destructs the input platform state
     *
     * state requires:
     *  - to have been constructed
     *
     * params:
     *  - FUR_platfState* state -- the input platform state
     */
void fur_platf_destr(FUR_platfState* state);

    /* fur_platf_shouldWindowClose func
     * returns if the window should store processing events
     *
     * state requires:
     *  - to have been constructed
     *
     * params
     *  - FUR_platfState* state -- the input platform state
     */
b8 fur_platf_shouldWindowClose(FUR_platfState* state);

    /* fur_platf_poll func
     * grabs input events
     *
     * state requires:
     *  - to have been constructed
     *
     * params
     *  - FUR_platfState* state -- the input platform state
     */
void fur_platf_poll(FUR_platfState* state);

    /* fur_platf_present func
     * presents/swaps the current window's buffer
     *
     * state requires:
     *  - to have been constructed
     *
     * params:
     *  - FUR_platfState* state -- the input platform state
     */
void fur_platf_present(FUR_platfState* state);

#endif
