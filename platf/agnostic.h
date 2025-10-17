#ifndef FUR_PLATFORM_AGNOSTIC_H
#define FUR_PLATFORM_AGNOSTIC_H

#include <core/macros.h>
#include <platf/state.h>

/* ====== FUNCS ====== */

    /* fur_platf_constr func
     * constructs and returns a FUR_platfState*
     * title must be set
     */
typedef struct {
    u8 _dummy;
    char* title;
    s32 width;
    s32 height;
    FUR_targetPlatf plat;
} OP_fur_platf_constr;
FUR_platfState* IMPL_fur_platf_constr(OP_fur_platf_constr ops);
#define fur_platf_constr(...) \
    IMPL_fur_platf_constr((OP_fur_platf_constr){0 __VA_OPT__(, __VA_ARGS__)})

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
     * NOTE: this is required in order to have the window not "freeze" according to the desktop
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
