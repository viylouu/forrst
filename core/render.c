#include <core/macros.h>
#include "render.h"
#include <core/load_gl.h>
#include <GL/gl.h>
#include <core/shader.h>

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


void fst_r2dRect_init(void* rect) {
    struct FST_r2dRect* state = rect;
    
    FST_r2dInitGeneric("data/eng/rect.vert", "data/eng/rect.frag");
} void fst_r2dRect_end(void* rect) {
    struct FST_r2dRect* state = rect;

    FST_r2dEndGeneric();
}

void fst_r2dTex_init(void* data) {
} void fst_r2dTex_end(void* data) {
}

/* [gl struct spritestack funcs] */
void fst_rSsCube_init(void* data) {
} void fst_rSsCube_end(void* data) {
}

void fst_rSsModel_init(void* data) {
} void fst_rSsModel_end(void* data) {
}

/*
 * [INIT]
 */

void* fst_render_init(void) {
    FSTrenderState* state = malloc(sizeof(FSTrenderState));

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
    FSTrenderState* state = data;

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
    FSTrenderState* state = data;
}

