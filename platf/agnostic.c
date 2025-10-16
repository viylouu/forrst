#include "agnostic.h"

#include <platf/glfw/main.h>

#include <core/macros.h>
#include <stdio.h>
#include <stdlib.h>

/* ====== MACROS ====== */

#define crit_def_for(func) default: ERROR("selected platform has no support for function \"%s\"!\n", func)
#define warn_def_for(func) defualt: WARN("selected platform has no support for function \"%s\"!\n", func)

/* ====== FUNCS ====== */

void fur_platf_constr(FUR_platfState* state) {
    switch(state->plat) {
        case FUR_PLATF_GLFW:
            fur_platf_glfw_constr(state->spec, state->title, state->width, state->height);
        crit_def_for("fur_platf_constr");
    }
}

void fur_platf_destr(FUR_platfState* state) {
    switch(state->plat) {
        case FUR_PLATF_GLFW:
            fur_platf_glfw_destr(state->spec);
        crit_def_for("fur_platf_destr");
    }
}
