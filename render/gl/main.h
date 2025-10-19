#ifndef FUR_RENDER_GL_MAIN_H
#define FUR_RENDER_GL_MAIN_H

#include <core/matrix.h>
#include <core/macros.h>
#include <render/state.h>
#include <render/gl/structs.h>

#include <core/data/shader.h>
#include <core/data/texture.h>

/* ====== STRUCTS ====== */

typedef enum {
    FUR_GL_BATCH_NONE,
    FUR_GL_BATCH_RECT,
    FUR_GL_BATCH_TEX
} FUR_gl_batchType;

typedef struct {
    FUR_renderState* agnostic;
    u32 shitty_vao;

    mat4 proj;

    FUR_gl_instanceData batch[65536];
    FUR_gl_batchType batch_type;
    u32 batch_amt;

    FUR_texture* nil;

    FUR_gl_2d_rect rect2d;
    FUR_gl_2d_tex  tex2d;
} FUR_gl_renderState;

/* ====== FUNCS ====== */

FUR_gl_renderState* fur_render_gl_constr(FUR_renderState* agnostic);
void fur_render_gl_destr(FUR_gl_renderState* state);

#endif
