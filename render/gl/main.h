#ifndef FUR_RENDER_GL_MAIN_H
#define FUR_RENDER_GL_MAIN_H

#include <core/macros.h>
#include <render/state.h>

/* ====== STRUCTS ====== */

typedef struct {
    FUR_renderState* agnostic;
    u32 shitty_vao;
} FUR_gl_renderState;

/* ====== FUNCS ====== */

FUR_gl_renderState* fur_render_gl_constr(FUR_renderState* agnostic);
void fur_render_gl_destr(FUR_gl_renderState* state);

#endif
