#ifndef FST_RENDER_H
#define FST_RENDER_H

#ifdef __cplusplus
extern "C" {
#endif

#include <core/macros.h>
#include <core/shader.h>

/* table of contents:
 * [CONSTS]
 * [GL STRUCTS]
 **** [gl struct 2d]
 **** [gl struct spritestack]
 * [STATE]
 * [INIT]
 * [END]
 * [UPDATE]
 **** [resize]
 */

/* [CONSTS] */
#define FST_MAX_BATCH_SIZE 8192
#define FST_MAX_BUFFER_SIZE FST_MAX_BATCH_SIZE*1 // sizeof(GLinstanceData)

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
#define FST_r2dGeneric() \
    FSTshader* shader; u32 bo, tbo;
#define FST_r2dGenericLoc() \
    s32 inst_size; s32 insts; s32 proj;


struct FST_r2dRect {
    FST_r2dGeneric();
    struct {
        FST_r2dGenericLoc();
    } loc;
};

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


struct FST_rSsModel {
    FST_rSsGeneric();
    struct {
        FST_rSsGenericLoc();
        s32 tex;
    } loc;
};

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
 * [INIT]
 */

void* fst_render_init(void);

/*
 * [END]
 */

void fst_render_end(void* data);

/*
 * [UPDATE]
 */

/* [resize] */
void fst_render_resize(void* data, s32 width, s32 height);

#ifdef __cplusplus
}
#endif

#endif
