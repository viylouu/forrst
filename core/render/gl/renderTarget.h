#ifndef FUR_RENDER_GL_RENDER_TARGET_H
#define FUR_RENDER_GL_RENDER_TARGET_H

#include <core/renderTarget.h>
#include <core/macros.h>

/* ====== DATATYPES ====== */

typedef struct {
    FUR_renderTarget* agnostic;

    u32 fbo, tex, depth;
} FUR_gl_renderTarget;

/* ====== FUNCS ====== */

FUR_gl_renderTarget* fur_renderTarget_gl_constr(FUR_renderTarget* agnostic, s32 width, s32 height);
void fur_renderTarget_gl_destr(FUR_gl_renderTarget* targ);

#endif
