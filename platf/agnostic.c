#include "agnostic.h"

#include <platf/glfw/main.h>

#include <core/macros.h>
#include <stdio.h>
#include <stdlib.h>

/* ====== FUNCS ====== */

FUR_platfState* IMPL_fur_platf_constr(OP_fur_platf_constr ops) {
    FUR_platfState* state = NEW(FUR_platfState);
    state->plat = ops.platf;
    state->title = ops.title;
    state->width = ops.dims.x;
    state->height = ops.dims.y;

    switch (state->plat) {
        case FUR_PLATF_GLFW:
            state->spec = fur_platf_glfw_constr(state); break;
        crit_def_for("fur_platf_constr");
    }
    
    return state;
}

void fur_platf_destr(FUR_platfState* state) {
    switch (state->plat) {
        case FUR_PLATF_GLFW:
            fur_platf_glfw_destr(state->spec); break;
        crit_def_for("fur_platf_destr");
    }

    free(state);
}

b8 fur_platf_shouldWindowClose(FUR_platfState* state) {
    switch (state->plat) {
        case FUR_PLATF_GLFW:
            return fur_platf_glfw_shouldWindowClose(state->spec);
        crit_def_for("fur_platf_shouldWindowClose");
    }
}

void fur_platf_poll(FUR_platfState* state) {
    switch (state->plat) {
        case FUR_PLATF_GLFW:
            fur_platf_glfw_poll(state->spec); break;
        crit_def_for("fur_platf_poll");
    }
}

void fur_platf_present(FUR_platfState* state) {
    switch (state->plat) {
        case FUR_PLATF_GLFW:
            fur_platf_glfw_present(state->spec); break;
        crit_def_for("fur_platf_present");
    }
}

void fur_platf_setRender(FUR_platfState* state, FUR_renderState* render) {
    switch (state->plat) {
        case FUR_PLATF_GLFW:
            fur_platf_glfw_setRender(state->spec, render); break;
        crit_def_for("fur_platf_setRender");
    }
}
