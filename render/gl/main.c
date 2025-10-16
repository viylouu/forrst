#include "main.h"

#include <render/gl/loader.h>

/* ====== FUNCS ====== */

void fur_render_gl_constr(FUR_gl_renderState* state) {
    fur_render_gl_load();

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glDepthMask(GL_TRUE);
    glDepthFunc(GL_LEQUAL);

    glGenVertexArrays(1, &state->shitty_vao);
}

void fur_render_gl_destr(FUR_gl_renderState* state) {
    glDeleteVertexArrays(1, &state->shitty_vao);
}
