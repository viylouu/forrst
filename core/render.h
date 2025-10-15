#ifndef FUR_RENDER_HH
#define FUR_RENDER_HH

#include <core/macros.h>
#include <core/shader.hh>
#include <core/texture.hh>
#include <core/mat4.h>
#include <vector>

namespace fur {
    class Render;
    class Render {
        /* table of contents:
         **** [2D structs]
         **** [Spritestack structs]
         **** [OTHER STRUCTS]
         **** [STATE]
         **** [CONSTS] -- not even really needed here tbh
         **** [INIT/END]
         **** [UPDATE]
         **** [FUNCS]
         */

private:
    /* [2D structs] */
    struct rSdGenericLoc { s32 inst_size, insts, proj; };
    struct rSdGeneric { Shader* shader; u32 bo, tbo; rSdGenericLoc loc; };

    struct rSdRect { rSdGeneric generic; };

    struct rSdTexLoc { s32 tex; };
    struct rSdTex { rSdGeneric generic; rSdTexLoc loc; };

    /* [Spritestack structs] */
    struct rSsGenericLoc { s32 inst_size, insts, proj, cam_rot, cam_pos, cam_z, cam_tile, cam_scale; };
    struct rSsGeneric { Shader* shad; u32 bo, tbo; rSsGenericLoc loc; };

    struct rSsCube { rSsGeneric generic; };

    struct rSsModelLoc { s32 tex; };
    struct rSsModel { rSsGeneric generic; rSsModelLoc loc; };

    /* [OTHER STRUCTS] */

    struct InstanceData {
        f32 x,y,w,h;
        f32 r,g,b,a;
        f32 sx,sy,sw,sh;
        mat4 transf;
    };

    enum BatchType {
        BATCH_2D_RECT,
        BATCH_2D_TEX,
        BATCH_SS_CUBE,
        BATCH_SS_MODEL
    };

private:
        /* [STATE] */

        // shit ass garbage vao
        u32 vao;

        

        mat4 ident;

        std::vector<InstanceData> batch;
        BatchType batch_type;
        Texture* batch_tex;

        mat4 proj2d;

        rSdRect sdRect;
        rSdTex sdTex;

        rSsCube ssCube;
        rSsModel ssModel;

        Texture* nil;

private:

        /* [CONSTS] */
#define FUR_MAX_BATCH_SIZE 8192
#define FUR_MAX_BUFFER_SIZE FUR_MAX_BATCH_SIZE * sizeof(InstanceData)


#define FUR_genericInitEnd(name)        \
        void name##_init();             \
        void name##_end();              \
        void name##_draw();

        FUR_genericInitEnd(rSdRect);
        FUR_genericInitEnd(rSdTex);
        FUR_genericInitEnd(rSsCube);
        FUR_genericInitEnd(rSsModel);

public:
        s32 width, height;

public:

        /*
         * [INIT/END]
         */

        Render();
        ~Render();

        /*
         * [UPDATE]
         */

        void resize(s32 width, s32 height);

        /*
         * [FUNCS]
         */

        void flush();
        void clear(v4 col);

        void rect(mat4 transf, v2 pos, v2 size, v4 col);
        void tex(Texture* tex, mat4 transf, v2 pos, v2 size, v4 sample, v4 col);
    };
}

#endif
