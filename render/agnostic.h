#ifndef FUR_RENDER_AGNOSTIC_H
#define FUR_RENDER_AGNOSTIC_H

#include <render/state.h>
#include <core/macros.h>

/* ====== DATATYPES ====== */
typedef struct {
    FUR_targetRenderApi api;
} OP_fur_render_constr;

/* ====== FUNCS ====== */

FUR_renderState* IMPL_fur_render_constr(OP_fur_render_constr ops);
void fur_render_destr(FUR_renderState* state);
void fur_render_resize(FUR_renderState* state, f32 w, f32 h);

/* ====== MACROS ====== */
#define fur_render_constr(...) \
    IMPL_fur_render_constr((OP_fur_render_constr){ .api = FUR_RENDER_API_GL, __VA_ARGS__ })

#endif
