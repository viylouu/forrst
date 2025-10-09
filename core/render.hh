#ifndef FUR_RENDER_HH
#define FUR_RENDER_HH

#include <core/macros.h>
#include <core/shader.h>
#include <vector>
#include <core/texture.h>
#include <core/mat4.h>

namespace fur {
    class Render;
    class Render {
        /* table of contents:
         **** [CONSTS]
         **** [GL STRUCTS]
         **** **** [gl struct 2d]
         **** **** [gl struct spritestack]
         **** [DATATYPES]
         **** [STATE]
         **** [INIT]
         **** [END]
         **** [UPDATE]
         **** **** [resize]
         **** [FUNCS]
         **** **** [funcs generic]
         **** **** [funcs 2d]
         */

        /* [CONSTS] */
#define FUR_MAX_BATCH_SIZE 8192
#define FUR_MAX_BUFFER_SIZE FUR_MAX_BATCH_SIZE * sizeof(FURinstanceData)

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
#define FUR_r2dGeneric() \
            FURshader* shader; u32 bo, tbo
#define FUR_r2dGenericLoc() \
            s32 inst_size; s32 insts; s32 proj


        struct FUR_r2dRect {
            FUR_r2dGeneric();
            struct {
                FUR_r2dGenericLoc();
            } loc;
        };

        struct FUR_r2dTex {
            FUR_r2dGeneric();
            struct {
                FUR_r2dGenericLoc();
                s32 tex;
            } loc;
        };

        /* [gl struct spritestack] */
#define FUR_rSsGeneric() \
            FURshader* shad; u32 bo, tbo
        // if this is too big... idgaf no it isnt
#define FUR_rSsGenericLoc() \
            s32 inst_size, insts, proj, cam_rot, cam_pos, cam_z, cam_tilt, cam_scale


        struct FUR_rSsCube {
            FUR_rSsGeneric();
            struct {
                FUR_rSsGenericLoc();
            } loc;
        };

        struct FUR_rSsModel {
            FUR_rSsGeneric();
            struct {
                FUR_rSsGenericLoc();
                s32 tex;
            } loc;
        };

        typedef struct {
            f32 x,y,w,h;
            f32 r,g,b,a;
            f32 sx,sy,sw,sh;
            mat4 transf;
        } FURinstanceData;

        typedef enum {
            FUR_BATCH_2D_RECT,
            FUR_BATCH_2D_TEX,
            FUR_BATCH_SS_CUBE,
            FUR_BATCH_SS_MODEL
        } FURbatchType;

        /*
         * [DATATYPES]
         */

        typedef struct {
            u32 fbo;
            u32 depth;
            FURtexture* tex;
            s32 width, height;
        } FURrenderTarget;

        void fur_renderTarget_unload(FURrenderTarget* targ);
        FURrenderTarget* fur_renderTarget_make(s32 width, s32 height);

        typedef struct {
            /*
             * [STATE]
             */

            // shit ass garbage vao
            u32 vao;

            s32 width, height;

            std::vector<FURinstanceData> batch;
            FURbatchType batch_type;
            FURtexture* batch_tex;
            FURrenderTarget* batch_targ;

            mat4 proj2d;

            struct FUR_r2dRect rect;
            struct FUR_r2dTex tex;

            struct FUR_rSsCube ssCube;
            struct FUR_rSsModel ssModel;
        } FURrenderState;

        /*
         * [INIT]
         */

        void* fur_render_init(void);

        /*
         * [END]
         */

        void fur_render_end(void* data);

        /*
         * [UPDATE]
         */

        /* [resize] */
        void fur_render_resize(void* data, s32 width, s32 height);

        /*
         * [FUNCS]
         */

        /* [funcs generic] */
        void fur_render_flush();
        void fur_render_clear(FURrenderTarget* targ, f32 r, f32 g, f32 b, f32 a);

        /* [funcs 2d] */
        void fur_render_rect(FURrenderTarget* targ, mat4 transf, f32 x, f32 y, f32 w, f32 h, f32 r, f32 g, f32 b, f32 a);
        void fur_render_tex(FURrenderTarget* targ, FURtexture* tex, mat4 transf, f32 x, f32 y, f32 w, f32 h, f32 sx, f32 sy, f32 sw, f32 sh, f32 r, f32 g, f32 b, f32 a);
        void fur_render_renderTarget(FURrenderTarget* targ, FURrenderTarget* rtarg, mat4 transf, f32 x, f32 y, f32 w, f32 h, f32 sx, f32 sy, f32 sw, f32 sh, f32 r, f32 g, f32 b, f32 a); // wow thats big
    };
}

#endif
