#include "agnostic.h"

#include <core/macros.h>
#include <stdio.h>
#include <stdlib.h>

/* ====== MACROS ====== */

#define crit_def_for(func) default: ERROR("selected api has no support for function \"%s\"!\n", func); break
#define warn_def_for(func) defualt: WARN("selected api has no support for function \"%s\"!\n", func); break

/* ====== FUNCS ====== */

void fur_render_constr(FUR_renderState* state) {
    switch(state->api) {
        case FUR_RENDER_API_GL:
            fur_render_gl_constr(state->spec); break;
        crit_def_for("fur_render_constr");
    }
}

void fur_render_destr(FUR_renderState* state) {
    switch(state->api) {
        case FUR_RENDER_API_GL:
            fur_render_gl_destr(state->spec); break;
        crit_def_for("fur_render_destr");
    }

    free(state);
}
