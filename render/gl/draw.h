#ifndef FUR_RENDER_GL_DRAW_H
#define FUR_RENDER_GL_DRAW_H

#include <render/gl/main.h>

/* ====== FUNCS ====== */

void fur_render_gl_clear(FUR_gl_renderState* render, f32 r, f32 g, f32 b);

void fur_render_gl_flush(FUR_gl_renderState* render);

/* ====== FUNCS ====== */

void fur_render_gl_rect(FUR_gl_renderState* render, mat4 transf, v2 pos, v2 size, v4 col);

#endif
