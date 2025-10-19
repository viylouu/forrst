#ifndef FUR_RENDER_AGNOSTIC_H
#define FUR_RENDER_AGNOSTIC_H

#include <render/state.h>
#include <core/macros.h>

/* ====== DATATYPES ====== */
typedef struct {
    u8 _dummy;
    FUR_targetRenderApi api;
} OP_fur_render_constr;

/* ====== FUNCS ====== */

FUR_renderState* IMPL_fur_render_constr(OP_fur_render_constr ops);
void fur_render_destr(FUR_renderState* state);

/* ====== MACROS ====== */
#define fur_render_constr(...) \
    IMPL_fur_render_constr((OP_fur_render_constr){0 __VA_OPT__(, __VA_ARGS__)})

#endif
