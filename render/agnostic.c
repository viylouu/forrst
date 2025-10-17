#include "agnostic.h"

#include <render/gl/main.h>
#include <render/state.h>
#include <core/macros.h>
#include <stdio.h>
#include <stdlib.h>

/* ====== MACROS ====== */

#define crit_def_for(func) default: ERROR("selected api has no support for function \"%s\"!\n", func); break
#define warn_def_for(func) defualt: WARN("selected api has no support for function \"%s\"!\n", func); break

/* ====== FUNCS ====== */

FUR_renderState* IMPL_fur_render_constr(OP_fur_render_constr ops) {
    FUR_renderState* state = NEW(FUR_renderState);
    state->api = ops.api;

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
