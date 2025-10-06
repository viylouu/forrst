#include <core/macros.h>
#include "render.hh"
#include <core/auto/load_gl.h>
#include <GL/gl.h>
#include <core/shader.h>
#include <core/mat4.h>
#include <core/texture.h>

/* table of contents:
 **** [GL STRUCTS]
 **** **** [gl struct 2d]
 **** **** [gl struct spritestack]
 **** [DATATYPES]
 **** [GL STRUCT FUNCS]
 **** **** [gl struct 2d funcs]
 **** **** [gl struct spritestack funcs]
 **** [INIT]
 **** [END]
 **** [UPDATE]
 **** **** [resize]
 **** [FUNCS]
 **** **** [funcs generic]
 **** **** [funcs 2d]
 */

#define FUR_useTarget(targ) do {                            \
    if (targ) {                                             \
        glBindFramebuffer(GL_FRAMEBUFFER, targ->fbo);       \
        glViewport(0,0,targ->tex->width,targ->tex->height); \
    } else {                                                \
        glBindFramebuffer(GL_FRAMEBUFFER, 0);               \
        glViewport(0,0,state->width,state->height);         \
    }                                                       \
} while(0)

/*
 * [GL STRUCTS]
 *
 * this is the data for opengl to use
 * very silly
 */

#define FUR_genericInitEnd(name)        \
    void fur_##name##_init(void* data); \
    void fur_##name##_end(void* data)

/* [gl struct 2d] */
FUR_genericInitEnd(r2dRect);
FUR_genericInitEnd(r2dTex);

/* [gl struct spritestack] */
FUR_genericInitEnd(rSsCube);
FUR_genericInitEnd(rSsModel);

/*
 * [GL STRUCT FUNCS]
 */

/* [gl struct 2d funcs] */

#define FUR_r2dInitGeneric(vert,frag)                                                \
    state->shader = fur_shader_load(vert,frag);                                      \
                                                                                     \
    glGenBuffers(1, &state->bo);                                                     \
    glBindBuffer(GL_TEXTURE_BUFFER, state->bo);                                      \
    glBufferData(GL_TEXTURE_BUFFER, FUR_MAX_BUFFER_SIZE, NULL, GL_DYNAMIC_DRAW);     \
                                                                                     \
    glGenTextures(1, &state->tbo);                                                   \
    glBindTexture(GL_TEXTURE_BUFFER, state->bo);                                     \
    glTexBuffer(GL_TEXTURE_BUFFER, GL_RGBA32F, state->bo);                           \
                                                                                     \
    state->loc.insts     = glGetUniformLocation(state->shader->shader, "insts");     \
    state->loc.inst_size = glGetUniformLocation(state->shader->shader, "inst_size"); \
    state->loc.proj      = glGetUniformLocation(state->shader->shader, "proj")
#define FUR_r2dEndGeneric()           \
    fur_shader_unload(state->shader); \
    glDeleteTextures(1, &state->tbo); \
    glDeleteBuffers(1, &state->bo)
#define FUR_r2dDrawGeneric(obj) do {                                                                            \
    FUR_useTarget(state->batch_targ);                                                                           \
                                                                                                                \
    glUseProgram(obj->shader->shader);                                                                          \
    glBindVertexArray(state->vao);                                                                              \
                                                                                                                \
    glUniformMatrix4fv(obj->loc.proj, 1,0, state->proj2d);                                                      \
                                                                                                                \
    glBindBuffer(GL_TEXTURE_BUFFER, obj->bo);                                                                   \
    glBufferSubData(GL_TEXTURE_BUFFER, 0, state->batch.size() * sizeof(FURinstanceData), state->batch.data());  \
                                                                                                                \
    glActiveTexture(GL_TEXTURE0);                                                                               \
    glBindTexture(GL_TEXTURE_BUFFER, obj->tbo);                                                                 \
    glUniform1i(obj->loc.insts, 0);                                                                             \
                                                                                                                \
    glUniform1i(obj->loc.inst_size, sizeof(FURinstanceData) / 16);                                              \
} while(0)


void fur_r2dRect_init(void* data) {
    FUR_r2dRect* state = (FUR_r2dRect*)data;

    FUR_r2dInitGeneric("data/eng/rect.vert", "data/eng/rect.frag");
} void fur_r2dRect_end(void* data) {
    FUR_r2dRect* state = (FUR_r2dRect*)data;

    FUR_r2dEndGeneric();
} void fur_r2dRect_draw(void* data, void* obj) {
    FURrenderState* state = (FURrenderState*)data;
    FUR_r2dRect* rect = (FUR_r2dRect*)obj;

    FUR_r2dDrawGeneric(rect);
    
    glDrawArraysInstanced(GL_TRIANGLES, 0,6, state->batch.size());
}

void fur_r2dTex_init(void* data) {
    FUR_r2dTex* state = (FUR_r2dTex*)data;

    FUR_r2dInitGeneric("data/eng/tex.vert", "data/eng/tex.frag");

    state->loc.tex = glGetUniformLocation(state->shader->shader, "tex");
} void fur_r2dTex_end(void* data) {
    FUR_r2dTex* state = (FUR_r2dTex*)data;

    FUR_r2dEndGeneric();
} void fur_r2dTex_draw(void* data, void* obj) {
    FURrenderState* state = (FURrenderState*)data;
    FUR_r2dTex* tex = (FUR_r2dTex*)obj;

    FUR_r2dDrawGeneric(tex);

    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, state->batch_tex->glid);
    glUniform1i(tex->loc.tex, 1);

    glDrawArraysInstanced(GL_TRIANGLES, 0,6, state->batch.size());
}

/* [gl struct spritestack funcs] */
void fur_rSsCube_init(void* data) {
} void fur_rSsCube_end(void* data) {
} void fur_rSsCube_draw(void* data, void* obj) {
}

void fur_rSsModel_init(void* data) {
} void fur_rSsModel_end(void* data) {
} void fur_rSsModel_draw(void* data, void* obj) {
}

/*
 * [DATATYPES]
 */

void fur_renderTarget_unload(FURrenderTarget* targ) {
    glDeleteFramebuffers(1, &targ->fbo);
    glDeleteRenderbuffers(1, &targ->depth);
    fur_texture_unload(targ->tex);
    free(targ);
}

FURrenderTarget* fur_renderTarget_make(s32 width, s32 height) {
    u32 fbo;
    glGenFramebuffers(1, &fbo);
    glBindFramebuffer(GL_FRAMEBUFFER, fbo);

    FURtexture* tex = fur_texture_make(width, height);

    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, tex->glid, 0);

    u32 depth;
    glGenRenderbuffers(1, &depth);
    glBindRenderbuffer(GL_RENDERBUFFER, depth);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT24, width, height);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, depth);

    ERROR_IF(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE, "framebuffer is not complete!\n");

    FURrenderTarget* targ = new FURrenderTarget();
    targ->tex = tex;
    targ->fbo = fbo;
    targ->depth = depth;
    targ->width = width;
    targ->height = height;

    return targ;
}

/*
 * [INIT]
 */

void* fur_render_init(void) {
    FURrenderState* state = new FURrenderState();

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glDepthMask(GL_TRUE);
    glDepthFunc(GL_LEQUAL);

    glGenVertexArrays(1, &state->vao);

    fur_r2dRect_init(&state->rect);
    fur_r2dTex_init(&state->tex);

    fur_rSsCube_init(&state->ssCube);
    fur_rSsModel_init(&state->ssModel);

    return state;
}

/*
 * [END]
 */

void fur_render_end(void* data) {
    FURrenderState* state = (FURrenderState*)data;

    fur_r2dRect_end(&state->rect);
    fur_r2dTex_end(&state->tex);

    fur_rSsCube_end(&state->ssCube);
    fur_rSsModel_end(&state->ssModel);

    glDeleteVertexArrays(1, &state->vao);

    free(state);
}

/*
 * [UPDATE]
 */

/* [resize] */
void fur_render_resize(void* data, s32 width, s32 height) {
    FURrenderState* state = (FURrenderState*)data;

    fur_mat4_ortho(&state->proj2d, 0,width,height,0,-2147483647.f,2147483647.f);

    state->width = width;
    state->height = height;
}

/*
 * [FUNCS]
 */

/* [funcs generic] */
void fur_render_flush(void* data) {
    FURrenderState* state = (FURrenderState*)data;

    switch(state->batch_type) {
        case FUR_BATCH_2D_RECT:
            fur_r2dRect_draw(data, &state->rect); break;
        case FUR_BATCH_2D_TEX:
            fur_r2dTex_draw(data, &state->tex); break;
        case FUR_BATCH_SS_CUBE:
            fur_rSsCube_draw(data, &state->ssCube); break;
        case FUR_BATCH_SS_MODEL:
            fur_rSsModel_draw(data, &state->ssModel); break;
    }

    state->batch.clear();
}

void fur_render_clear(void* data, FURrenderTarget* targ, f32 r, f32 g, f32 b, f32 a) {
    FURrenderState* state = (FURrenderState*)data;

    FUR_useTarget(targ);

    glClearColor(r,g,b,a);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

/* [funcs 2d] */
void fur_render_rect(void* data, FURrenderTarget* targ, mat4 transf, f32 x, f32 y, f32 w, f32 h, f32 r, f32 g, f32 b, f32 a) {
    FURrenderState* state = (FURrenderState*)data;

    if (state->batch_type != FUR_BATCH_2D_RECT) fur_render_flush(data);
    if (state->batch.size() >= FUR_MAX_BATCH_SIZE) fur_render_flush(data);
    if (state->batch_targ != targ) fur_render_flush(data);

    state->batch_type = FUR_BATCH_2D_RECT;

    FURinstanceData inst;

    std::copy(transf,transf+16,inst.transf);

    inst.x = x;
    inst.y = y;
    inst.w = w;
    inst.h = h;
    inst.r = r;
    inst.g = g;
    inst.b = b;
    inst.a = a;

    state->batch.push_back(inst);
}

void fur_render_tex(void* data, FURrenderTarget* targ, FURtexture* tex, mat4 transf, f32 x, f32 y, f32 w, f32 h, f32 sx, f32 sy, f32 sw, f32 sh, f32 r, f32 g, f32 b, f32 a) {
    FURrenderState* state = (FURrenderState*)data;

    if (state->batch_type != FUR_BATCH_2D_TEX) fur_render_flush(data);
    if (state->batch.size() >= FUR_MAX_BATCH_SIZE) fur_render_flush(data);
    if (state->batch_tex != tex) fur_render_flush(data);
    if (state->batch_targ != targ) fur_render_flush(data);

    state->batch_type = FUR_BATCH_2D_TEX;
    state->batch_tex = tex;
    state->batch_targ = targ;

    //printf("%p (targ: %p)\n", state->batch_targ, targ);

    FURinstanceData inst;

    std::copy(transf,transf+16,inst.transf);

    inst.x = x;
    inst.y = y;
    inst.w = w;
    inst.h = h;
    inst.r = r;
    inst.g = g;
    inst.b = b;
    inst.a = a;

    if(targ) {
        if (tex) {
            inst.sx = sx / (f32)tex->width;
            inst.sy = sy / (f32)tex->height;
            inst.sw = sw / (f32)tex->width;
            inst.sh = sh / (f32)tex->height;
        } else {
            inst.sx = sx / (f32)targ->tex->width;
            inst.sy = sy / (f32)targ->tex->height;
            inst.sw = sw / (f32)targ->tex->width;
            inst.sh = sh / (f32)targ->tex->height;
        }
    } else {
        inst.sx = sx / state->width;
        inst.sy = sy / state->height;
        inst.sw = sw / state->width;
        inst.sh = sh / state->height;
    }

    state->batch.push_back(inst);
}

void fur_render_renderTarget(void* data, FURrenderTarget* targ, FURrenderTarget* rtarg, mat4 transf, f32 x, f32 y, f32 w, f32 h, f32 sx, f32 sy, f32 sw, f32 sh, f32 r, f32 g, f32 b, f32 a) {
    fur_render_tex(data, targ, rtarg->tex, transf, x,y,w,h, sx,sy,sw,sh, r,g,b,a);
}
