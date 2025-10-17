#include "agnostic.h"

#include <platf/glfw/main.h>

#include <core/macros.h>
#include <stdio.h>
#include <stdlib.h>

/* ====== MACROS ====== */

#define crit_def_for(func) default: ERROR("selected platform has no support for function \"%s\"!\n", func); break
#define warn_def_for(func) defualt: WARN("selected platform has no support for function \"%s\"!\n", func); break

/* ====== FUNCS ====== */

void fur_platf_constr(FUR_platfState* state) {
    switch(state->plat) {
        case FUR_PLATF_GLFW:
            fur_platf_glfw_constr(state->spec, state); break;
        crit_def_for("fur_platf_constr");
    }
}

void fur_platf_destr(FUR_platfState* state) {
    switch(state->plat) {
        case FUR_PLATF_GLFW:
            fur_platf_glfw_destr(state->spec); break;
        crit_def_for("fur_platf_destr");
    }

    free(state);
}

b8 fur_platf_shouldWindowClose(FUR_platfState* state) {
    switch(state->plat) {
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
