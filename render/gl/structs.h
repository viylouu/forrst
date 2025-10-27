#ifndef FUR_RENDER_GL_STRUCTS_H
#define FUR_RENDER_GL_STRUCTS_H

#include <core/macros.h>
#include <core/data/shader.h>
#include <core/renderTarget.h>
#include <core/data/api/gl/texture.h>
#include <render/gl/misc.h>

/* ====== MACROS ====== */

#define easy_set_target(proj2d, targ, w,h) do { \
    if (targ) { \
        mat4_ortho(proj2d, 0,targ->texture->width,targ->texture->height,0, -1,1); \
        glViewport(0,0,targ->texture->width,targ->texture->height); \
        glBindFramebuffer(GL_FRAMEBUFFER, CAST(FUR_gl_renderTarget*, targ->spec)->fbo); \
    } else { \
        mat4_ortho(proj2d, 0,w,h,0, -1,1); \
        glViewport(0,0,w,h); \
        glBindFramebuffer(GL_FRAMEBUFFER, 0); \
    } \
} while(0)

/* ====== DATATYPES ====== */

typedef struct { s32 inst_size, insts, proj; }                                  FUR_gl_2d_genericLoc;
typedef struct { FUR_shader* shader; u32 bo, tbo; FUR_gl_2d_genericLoc loc; }   FUR_gl_2d_generic;

typedef struct { FUR_gl_2d_generic generic; }                                   FUR_gl_2d_rect;

typedef struct { s32 tex; }                                                     FUR_gl_2d_texLoc;
typedef struct { FUR_gl_2d_generic generic; FUR_gl_2d_texLoc loc; }             FUR_gl_2d_tex;

typedef struct { s32 tex; }                                                     FUR_gl_2d_renderTargetLoc;
typedef struct { FUR_gl_2d_generic generic; FUR_gl_2d_renderTargetLoc loc; }    FUR_gl_2d_renderTarget;

/* ====== FUNCS ====== */

void fur_render_gl_2d_rect_constr(FUR_gl_2d_rect* rect);
void fur_render_gl_2d_rect_destr(FUR_gl_2d_rect* rect);
void fur_render_gl_2d_rect_draw(FUR_gl_2d_rect* rect, mat4* proj2d, u32 vao, FUR_gl_instanceData (*batch)[8192], u32 batch_amt, FUR_renderTarget* batch_target, s32 width, s32 height);

void fur_render_gl_2d_tex_constr(FUR_gl_2d_tex* tex);
void fur_render_gl_2d_tex_destr(FUR_gl_2d_tex* tex);
void fur_render_gl_2d_tex_draw(FUR_gl_2d_tex* tex, mat4* proj2d, u32 vao, FUR_gl_instanceData (*batch)[8192], u32 batch_amt, FUR_gl_texture* batch_tex, FUR_renderTarget* batch_target, s32 width, s32 height);

void fur_render_gl_2d_renderTarget_constr(FUR_gl_2d_renderTarget* targ);
void fur_render_gl_2d_renderTarget_destr(FUR_gl_2d_renderTarget* targ);
void fur_render_gl_2d_renderTarget_draw(FUR_gl_2d_renderTarget* targ, mat4* proj2d, u32 vao, FUR_gl_instanceData (*batch)[8192], u32 batch_amt, FUR_renderTarget* batch_in_target, FUR_renderTarget* batch_out_target, s32 width, s32 height);

#endif
