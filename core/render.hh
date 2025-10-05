#ifndef FST_RENDER_HH
#define FST_RENDER_HH

#include <core/macros.h>
#include <core/shader.h>
#include <vector>
#include <core/mat4.h>

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
 * [FUNCS]
 **** [funcs generic]
 **** **** [funcs generic - transform]
 **** [funcs 2d]
 */

/* [CONSTS] */
#define FST_MAX_BATCH_SIZE 8192
#define FST_MAX_BUFFER_SIZE FST_MAX_BATCH_SIZE * sizeof(FSTinstanceData)

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
    FSTshader* shader; u32 bo, tbo
#define FST_r2dGenericLoc() \
    s32 inst_size; s32 insts; s32 proj


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
    FSTshader* shad; u32 bo, tbo
// if this is too big... idgaf no it isnt
#define FST_rSsGenericLoc() \
    s32 inst_size, insts, proj, cam_rot, cam_pos, cam_z, cam_tilt, cam_scale


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
    f32 x,y,w,h;
    f32 r,g,b,a;
    f32 sx,sy,sw,sh;
    float transf[16];
} FSTinstanceData;

typedef enum {
    FST_BATCH_2D_RECT,
    FST_BATCH_2D_TEX,
    FST_BATCH_SS_CUBE,
    FST_BATCH_SS_MODEL
} FSTbatchType;

typedef struct {
    /*
     * [STATE]
     */

    // shit ass garbage vao
    u32 vao;

    std::vector<FSTinstanceData> batch;
    FSTbatchType batch_type;

    mat4 proj2d;

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

/*
 * [FUNCS]
 */

/* [funcs generic] */
void fst_render_flush(void* data);
void fst_render_clear(void* data, f32 r, f32 g, f32 b, f32 a);

/**** [funcs generic - transform] */

/* [funcs 2d] */
void fst_render_rect(void* data, mat4 transf, f32 x, f32 y, f32 w, f32 h, f32 r, f32 g, f32 b, f32 a);

#endif
