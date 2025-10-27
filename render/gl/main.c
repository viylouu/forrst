#include "main.h"

#include <render/api.h>
#include <render/gl/loader.h>
#include <render/gl/structs.h>
#include <stdlib.h>

#include <core/data/shader.h>

/* ====== FUNCS ====== */

FUR_gl_renderState* fur_render_gl_constr(FUR_renderState* agnostic) {
    //const FUR_targetRenderApi api = FUR_RENDER_API_GL;

    FUR_gl_renderState* state = NEW(FUR_gl_renderState);
    state->agnostic = agnostic;

    fur_render_gl_load();

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glDepthMask(GL_TRUE);
    glDepthFunc(GL_LEQUAL);

    glGenVertexArrays(1, &state->shitty_vao);

    mat4_set_identity(&state->proj);

    fur_render_gl_2d_rect_constr(&state->rect2d);
    fur_render_gl_2d_tex_constr(&state->tex2d);

    return state;
}

void fur_render_gl_destr(FUR_gl_renderState* state) {
    const FUR_targetRenderApi api = FUR_RENDER_API_GL;

    fur_render_gl_2d_tex_destr(&state->tex2d);
    fur_render_gl_2d_rect_destr(&state->rect2d);

    glDeleteVertexArrays(1, &state->shitty_vao);

    fur_texture_unload(state->nil, .api = api);

    free(state);
}

void fur_render_gl_resize(FUR_gl_renderState* state, f32 w, f32 h) {
    //mat4_ortho(&state->proj, 0,w,h,0, -1,1);
    //glViewport(0,0,w,h);
    state->width = w;
    state->height = h;
}
