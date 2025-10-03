#include <core/macros.h>
#include "render.h"
#include <core/load_gl.h>
#include <GL/gl.h>

/* table of contents:
 **** you can search for any of these points to hop to it in the code!
 **** [CONSTS]
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
 * [CONSTS]
 */

#define FST_MAX_BATCH_SIZE 8192
#define FST_MAX_BUFFER_SIZE FST_MAX_BATCH_SIZE*1 // sizeof(GLinstanceData)

/*
 * [GL STRUCTS]
 *
 * this is the data for opengl to use
 * very silly
 */

#define FST_genericInitEnd(name) \
    void fst_##name##_init(void* data); \
    void fst_##name##_end(void* data)

/* [gl struct 2d] */
#define FST_r2dGeneric() \
    u32 prog; u32 bo, tbo;
#define FST_r2dGenericLoc() \
    s32 inst_size; s32 insts; s32 proj;


struct FST_r2dRect {
    FST_r2dGeneric();
    struct {
        FST_r2dGenericLoc();
    } loc;
};

FST_genericInitEnd(r2dRect);

struct FST_r2dTex {
    FST_r2dGeneric();
    struct {
        FST_r2dGenericLoc();
        s32 tex;
    } loc;
};

FST_genericInitEnd(r2dTex);

/* [gl struct spritestack] */
#define FST_rSsGeneric() \
    u32 prog; u32 bo, tbo;
// if this is too big... idgaf no it isnt
#define FST_rSsGenericLoc() \
    s32 inst_size, insts, proj, cam_rot, cam_pos, cam_z, cam_tilt, cam_scale;


struct FST_rSsCube {
    FST_rSsGeneric();
    struct {
        FST_rSsGenericLoc();
    } loc;
};

FST_genericInitEnd(rSsCube);

struct FST_rSsModel {
    FST_rSsGeneric();
    struct {
        FST_rSsGenericLoc();
        s32 tex;
    } loc;
};

FST_genericInitEnd(rSsModel);

typedef struct {
    /*
     * [STATE]
     */

    // shit ass garbage vao
    u32 vao;

    struct FST_r2dRect rect;
    struct FST_r2dTex tex;

    struct FST_rSsCube ssCube;
    struct FST_rSsModel ssModel;
} FSTrenderState;

/*
 * [GL STRUCT FUNCS]
 */

/* [gl struct 2d funcs] */

#define FST_r2dInitGeneric() \
    glGenBuffers(1, &state->bo); \
    glBindBuffer(GL_TEXTURE_BUFFER, state->bo); \
    glBufferData(GL_TEXTURE_BUFFER, FST_MAX_BUFFER_SIZE, NULL, GL_DYNAMIC_DRAW); \
\
    glGenTextures(1, &state->tbo); \
    glBindTexture(GL_TEXTURE_BUFFER, state->bo); \
    glTexBuffer(GL_TEXTURE_BUFFER, GL_RGBA32F, state->bo)
#define FST_r2dEndGeneric() \
    glDeleteTextures(1, &state->tbo); \
    glDeleteBuffers(1, &state->bo)


void fst_r2dRect_init(void* rect) {
    struct FST_r2dRect* state = rect;
    
    FST_r2dInitGeneric();
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


