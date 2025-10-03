#include <core/macros.h>
#include "render.h"

/* table of contents:
 **** you can search for any of these points to hop to it in the code!
 **** [GL STRUCTS]
 **** **** [gl struct 2d]
 **** **** [gl struct spritestack]
 **** [STATE]
 */

/*
 * [GL STRUCTS]
 *
 * this is the data for opengl to use
 * very silly
 */

// shit ass garbage vao
u32 vao;

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

struct FST_r2dTex {
    FST_r2dGeneric();
    struct {
        FST_r2dGenericLoc();
        s32 tex;
    } loc;
};

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

    struct FST_r2dRect rect;
    struct FST_r2dTex tex;

    struct FST_rSsCube ssCube;
    struct FST_rSsModel ssModel;
} FSTrenderState;

void* fst_render_init(void) {
    FSTrenderState* state = malloc(sizeof(FSTrenderState));

    return state;
}

void fst_render_resize(void* state, s32 width, s32 height) {

}

void fst_render_end(void* state) {
    free(state);
}
