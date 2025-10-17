#ifndef FUR_RENDER_AGNOSTIC_H
#define FUR_RENDER_AGNOSTIC_H

#include <render/state.h>

/* ====== FUNCS ====== */

    /* fur_render_constr func
     * constructs the input render state
     */
typedef struct {
    FUR_targetRenderApi api;
} OP_fur_render_constr;
FUR_renderState* IMPL_fur_render_constr(OP_fur_render_constr ops);
#define fur_render_constr(...)                     \
    IMPL_fur_render_constr((OP_fur_render_constr){ \
            .api = FUR_RENDER_API_GL,              \
            __VA_ARGS__})

    /* fur_render_destr func
     * destructs the input render state
     *
     * params
     * - FUR_renderState* state -- the input render state
     */
void fur_render_destr(FUR_renderState* state);

#endif
