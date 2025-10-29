#include "structs.h"

#include <core/data/shader.h>
#include <core/render/gl/renderTarget.h>
#include <core/data/api/gl/shader.h>
#include <core/data/api/gl/texture.h>
#include <render/gl/loader.h>
#include <stdlib.h>
#include <stdio.h>

/* ====== MACROS ====== */

#define easy_shader_prog(obj) \
    ((FUR_gl_shader*)obj->generic.shader->spec)->program
#define easy_get_uni(obj, name) \
    glGetUniformLocation(easy_shader_prog(obj), name)

#define FUR_2D_GENERIC_CONSTR(obj, vert,frag) do { \
    obj->generic.shader = fur_shader_load((vert),(frag), .api = FUR_RENDER_API_GL); \
\
    glGenBuffers(1, &obj->generic.bo); \
    glBindBuffer(GL_TEXTURE_BUFFER, obj->generic.bo); \
    glBufferData(GL_TEXTURE_BUFFER, 8192 * sizeof(FUR_gl_instanceData), NULL, GL_DYNAMIC_DRAW); \
\
    glGenTextures(1, &obj->generic.tbo); \
    glBindTexture(GL_TEXTURE_BUFFER, obj->generic.tbo); \
    glTexBuffer(GL_TEXTURE_BUFFER, GL_RGBA32F, obj->generic.bo); \
\
    obj->generic.loc.insts     = easy_get_uni(obj, "insts"); \
    obj->generic.loc.inst_size = easy_get_uni(obj, "inst_size"); \
    obj->generic.loc.proj      = easy_get_uni(obj, "proj"); \
} while(0)

#define FUR_2D_GENERIC_DESTR(obj) do { \
    fur_shader_unload(obj->generic.shader, .api = FUR_RENDER_API_GL); \
\
    glDeleteTextures(1, &obj->generic.tbo); \
    glDeleteBuffers(1, &obj->generic.bo); \
} while(0)

#define FUR_2D_GENERIC_DRAW(obj, vao, batch, batch_amt, proj2d, targ, width, height) do { \
    easy_set_target(proj2d, targ, width, height); \
\
    glUseProgram(easy_shader_prog(obj)); \
    glBindVertexArray(vao); \
\
    glUniformMatrix4fv(obj->generic.loc.proj, 1,0, *proj2d); \
\
    glBindBuffer(GL_TEXTURE_BUFFER, obj->generic.bo); \
    glBufferSubData(GL_TEXTURE_BUFFER, 0, batch_amt * sizeof(FUR_gl_instanceData), *batch); \
\
    glActiveTexture(GL_TEXTURE0); \
    glBindTexture(GL_TEXTURE_BUFFER, obj->generic.tbo); \
    glUniform1i(obj->generic.loc.insts, 0); \
\
    glUniform1i(obj->generic.loc.inst_size, sizeof(FUR_gl_instanceData) / 16); \
} while(0)

/* ====== FUNCS ====== */

void fur_render_gl_2d_rect_constr(FUR_gl_2d_rect* rect) { FUR_2D_GENERIC_CONSTR(rect, "data/eng/rect.vert", "data/eng/rect.frag"); } 
void fur_render_gl_2d_rect_destr(FUR_gl_2d_rect* rect) { FUR_2D_GENERIC_DESTR(rect); } 
void fur_render_gl_2d_rect_draw(FUR_gl_2d_rect* rect, mat4* proj2d, u32 vao, FUR_gl_instanceData (*batch)[8192], u32 batch_amt, FUR_renderTarget* batch_target, s32 width, s32 height) {
    FUR_2D_GENERIC_DRAW(rect, vao, batch, batch_amt, proj2d, batch_target, width, height);

    glDrawArraysInstanced(GL_TRIANGLES, 0,6, batch_amt);
}

void fur_render_gl_2d_tex_constr(FUR_gl_2d_tex* tex) {
    FUR_2D_GENERIC_CONSTR(tex, "data/eng/tex.vert", "data/eng/tex.frag");

    tex->loc.tex = easy_get_uni(tex, "tex");
} 
void fur_render_gl_2d_tex_destr(FUR_gl_2d_tex* tex) { FUR_2D_GENERIC_DESTR(tex); } 
void fur_render_gl_2d_tex_draw(FUR_gl_2d_tex* tex, mat4* proj2d, u32 vao, FUR_gl_instanceData (*batch)[8192], u32 batch_amt, FUR_gl_texture* batch_tex, FUR_renderTarget* batch_target, s32 width, s32 height) {
    FUR_2D_GENERIC_DRAW(tex, vao, batch, batch_amt, proj2d, batch_target, width, height);

    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, batch_tex->id);
    glUniform1i(tex->loc.tex, 1);

    glDrawArraysInstanced(GL_TRIANGLES, 0,6, batch_amt);
}

void fur_render_gl_2d_renderTarget_constr(FUR_gl_2d_renderTarget* targ) {
    FUR_2D_GENERIC_CONSTR(targ, "data/eng/tex.vert", "data/eng/tex.frag");

    targ->loc.tex = easy_get_uni(targ, "tex");
} 
void fur_render_gl_2d_renderTarget_destr(FUR_gl_2d_renderTarget* targ) { FUR_2D_GENERIC_DESTR(targ); } 
void fur_render_gl_2d_renderTarget_draw(FUR_gl_2d_renderTarget* targ, mat4* proj2d, u32 vao, FUR_gl_instanceData (*batch)[8192], u32 batch_amt, FUR_renderTarget* batch_in_target, FUR_renderTarget* batch_out_target, s32 width, s32 height) {
    FUR_2D_GENERIC_DRAW(targ, vao, batch, batch_amt, proj2d, batch_out_target, width, height);

    FUR_gl_texture* gltex = batch_in_target->texture->spec;

    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, gltex->id);
    glUniform1i(targ->loc.tex, 1);

    glDrawArraysInstanced(GL_TRIANGLES, 0,6, batch_amt);
}

