#ifndef FUR_RENDER_GL_MAIN_H
#define FUR_RENDER_GL_MAIN_H

#include <core/macros.h>
#include <render/state.h>

#include <core/data/shader.h>
#include <core/data/texture.h>

/* ====== STRUCTS ====== */

typedef struct { s32 inst_size, insts, proj; }                              FUR_2d_genericLoc;
typedef struct { FUR_shader* shader; u32 bo, tbo; FUR_2d_genericLoc loc; }  FUR_2d_generic;

typedef struct { FUR_2d_generic generic; }                                  FUR_2d_rect;

typedef struct { s32 tex; }                                                 FUR_2d_texLoc;
typedef struct { FUR_2d_generic generic; FUR_2d_texLoc loc; }               FUR_2d_tex;

typedef struct {
    FUR_renderState* agnostic;
    u32 shitty_vao;

    FUR_texture* nil;

    FUR_2d_rect rect2d;
    FUR_2d_tex  tex2d;
} FUR_gl_renderState;

/* ====== FUNCS ====== */

FUR_gl_renderState* fur_render_gl_constr(FUR_renderState* agnostic);
void fur_render_gl_destr(FUR_gl_renderState* state);

#endif
