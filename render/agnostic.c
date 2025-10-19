#include "agnostic.h"

#include <render/gl/main.h>
#include <render/state.h>
#include <core/macros.h>
#include <stdio.h>
#include <stdlib.h>

/* ====== FUNCS ====== */

FUR_renderState* IMPL_fur_render_constr(OP_fur_render_constr ops) {
    FUR_renderState* state = NEW(FUR_renderState);
    state->api = FUR_RENDER_API_GL;

    if (ops.api) state->api = ops.api;

    switch(state->api) {
        case FUR_RENDER_API_GL:
            state->spec = fur_render_gl_constr(state); break;
        crit_def_for("fur_render_constr");
    }

    return state;
}

void fur_render_destr(FUR_renderState* state) {
    switch(state->api) {
        case FUR_RENDER_API_GL:
            fur_render_gl_destr(state->spec); break;
        crit_def_for("fur_render_destr");
    }

    free(state);
}
