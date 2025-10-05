#include <core/macros.h>
#include "render.hh"
#include <core/auto/load_gl.h>
#include <GL/gl.h>
#include <core/shader.h>
#include <core/mat4.h>

/* table of contents:
 **** [GL STRUCTS]
 **** **** [gl struct 2d]
 **** **** [gl struct spritestack]
 **** [STATE]
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

/*
 * [GL STRUCTS]
 *
 * this is the data for opengl to use
 * very silly
 */

#define FST_genericInitEnd(name)        \
    void fst_##name##_init(void* data); \
    void fst_##name##_end(void* data)

/* [gl struct 2d] */
FST_genericInitEnd(r2dRect);
FST_genericInitEnd(r2dTex);

/* [gl struct spritestack] */
FST_genericInitEnd(rSsCube);
FST_genericInitEnd(rSsModel);

/*
 * [GL STRUCT FUNCS]
 */

/* [gl struct 2d funcs] */

#define FST_r2dInitGeneric(vert,frag)                                                \
    state->shader = fst_shader_load(vert,frag);                                      \
                                                                                     \
    glGenBuffers(1, &state->bo);                                                     \
    glBindBuffer(GL_TEXTURE_BUFFER, state->bo);                                      \
    glBufferData(GL_TEXTURE_BUFFER, FST_MAX_BUFFER_SIZE, NULL, GL_DYNAMIC_DRAW);     \
                                                                                     \
    glGenTextures(1, &state->tbo);                                                   \
    glBindTexture(GL_TEXTURE_BUFFER, state->bo);                                     \
    glTexBuffer(GL_TEXTURE_BUFFER, GL_RGBA32F, state->bo);                           \
                                                                                     \
    state->loc.insts     = glGetUniformLocation(state->shader->shader, "insts");     \
    state->loc.inst_size = glGetUniformLocation(state->shader->shader, "inst_size"); \
    state->loc.proj      = glGetUniformLocation(state->shader->shader, "proj")
#define FST_r2dEndGeneric()           \
    fst_shader_unload(state->shader); \
    glDeleteTextures(1, &state->tbo); \
    glDeleteBuffers(1, &state->bo)
#define FST_r2dDrawGeneric(rect) do { \
    glUseProgram(rect->shader->shader); \
    glBindVertexArray(state->vao); \
\
    glUniformMatrix4fv(rect->loc.proj, 1,0, state->proj2d); \
\
    glBindBuffer(GL_TEXTURE_BUFFER, rect->bo); \
    glBufferSubData(GL_TEXTURE_BUFFER, 0, state->batch.size() * sizeof(FSTinstanceData), state->batch.data()); \
\
    glActiveTexture(GL_TEXTURE0); \
    glBindTexture(GL_TEXTURE_BUFFER, rect->tbo); \
    glUniform1i(rect->loc.insts, 0); \
\
    glUniform1i(rect->loc.inst_size, sizeof(FSTinstanceData) / 16); \
} while(0)


void fst_r2dRect_init(void* rect) {
    FST_r2dRect* state = (FST_r2dRect*)rect;

    FST_r2dInitGeneric("data/eng/rect.vert", "data/eng/rect.frag");
} void fst_r2dRect_end(void* rect) {
    FST_r2dRect* state = (FST_r2dRect*)rect;

    FST_r2dEndGeneric();
} void fst_r2dRect_draw(void* data, void* obj) {
    FSTrenderState* state = (FSTrenderState*)data;
    FST_r2dRect* rect = (FST_r2dRect*)obj;

    FST_r2dDrawGeneric(rect);
    
    glDrawArraysInstanced(GL_TRIANGLES, 0,6, state->batch.size());
}

void fst_r2dTex_init(void* data) {
} void fst_r2dTex_end(void* data) {
} void fst_r2dTex_draw(void* data, void* obj) {
}

/* [gl struct spritestack funcs] */
void fst_rSsCube_init(void* data) {
} void fst_rSsCube_end(void* data) {
} void fst_rSsCube_draw(void* data, void* obj) {
}

void fst_rSsModel_init(void* data) {
} void fst_rSsModel_end(void* data) {
} void fst_rSsModel_draw(void* data, void* obj) {
}

/*
 * [INIT]
 */

void* fst_render_init(void) {
    FSTrenderState* state = new FSTrenderState();

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glDepthMask(GL_TRUE);
    glDepthFunc(GL_LEQUAL);

    glGenVertexArrays(1, &state->vao);

    fst_r2dRect_init(&state->rect);
    fst_r2dTex_init(&state->tex);

    fst_rSsCube_init(&state->ssCube);
    fst_rSsModel_init(&state->ssModel);

    return state;
}

/*
 * [END]
 */

void fst_render_end(void* data) {
    FSTrenderState* state = (FSTrenderState*)data;

    fst_r2dRect_end(&state->rect);
    fst_r2dTex_end(&state->tex);

    fst_rSsCube_end(&state->ssCube);
    fst_rSsModel_end(&state->ssModel);

    glDeleteVertexArrays(1, &state->vao);

    free(state);
}

/*
 * [UPDATE]
 */

/* [resize] */
void fst_render_resize(void* data, s32 width, s32 height) {
    FSTrenderState* state = (FSTrenderState*)data;

    printf("%p\n", state);
    fst_mat4_ortho(&state->proj2d, 0,width,height,0,-2147483647.f,2147483647.f);
}

/*
 * [FUNCS]
 */

/* [funcs generic] */
void fst_render_flush(void* data) {
    FSTrenderState* state = (FSTrenderState*)data;

    switch(state->batch_type) {
        case FST_BATCH_2D_RECT:
            fst_r2dRect_draw(data, &state->rect); break;
        case FST_BATCH_2D_TEX:
            fst_r2dTex_draw(data, &state->tex); break;
        case FST_BATCH_SS_CUBE:
            fst_rSsCube_draw(data, &state->ssCube); break;
        case FST_BATCH_SS_MODEL:
            fst_rSsModel_draw(data, &state->ssModel); break;
    }

    state->batch.clear();
}

void fst_render_clear(void* data, f32 r, f32 g, f32 b, f32 a) {
    UNUSED(data);
    glClearColor(r,g,b,a);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

/* [funcs 2d] */
void fst_render_rect(void* data, mat4 transf, f32 x, f32 y, f32 w, f32 h, f32 r, f32 g, f32 b, f32 a) {
    FSTrenderState* state = (FSTrenderState*)data;

    if (state->batch_type != FST_BATCH_2D_RECT) fst_render_flush(data);
    if (state->batch.size() >= FST_MAX_BATCH_SIZE) fst_render_flush(data);

    state->batch_type = FST_BATCH_2D_RECT;

    FSTinstanceData inst;

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
