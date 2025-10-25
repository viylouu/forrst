#include "input.h"

#include <core/macros.h>
#include <stdio.h>

#include <core/platf/glfw/input.h>

FUR_keyState fur_input_keys[FUR_KEY_LAST];

void fur_input_poll(FUR_platfState* platf) {
    switch (platf->plat) {
        case FUR_PLATF_GLFW:
            fur_input_glfw_poll(platf->spec); break;
        warn_def_for("fur_input_poll");
    }
}
