#include "main.h"

#include <render/gl/loader.h>
#include <stdlib.h>

#include <core/data/shader.h>

/* ====== FUNCS ====== */

FUR_gl_renderState* fur_render_gl_constr(FUR_renderState* agnostic) {
    const FUR_targetRenderApi api = FUR_RENDER_API_GL;

    FUR_gl_renderState* state = NEW(FUR_gl_renderState);
    state->agnostic = agnostic;

    fur_render_gl_load();

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glDepthMask(GL_TRUE);
    glDepthFunc(GL_LEQUAL);

    glGenVertexArrays(1, &state->shitty_vao);

    state->nil = fur_texture_load(api, "data/eng/nil.png");

    return state;
}

void fur_render_gl_destr(FUR_gl_renderState* state) {
    const FUR_targetRenderApi api = FUR_RENDER_API_GL;

    glDeleteVertexArrays(1, &state->shitty_vao);

    fur_texture_unload(api, state->nil);

    free(state);
}
