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
         **** [CONSTS]
         **** [some shi]
         **** [STATE]
         **** [INIT/END]
         **** [UPDATE]
         **** [FUNCS]
         */

private:
        // shit ass garbage vao
        u32 vao;

        s32 width, height;

        std::vector<InstanceData> batch;
        BatchType batch_type;
        Texture* batch_tex;

        mat4 proj2d;

        r2dRect sdRect;
        r2dTex sdTex;

        rSsCube ssCube;
        rSsModel ssModel;

private:

        /* [CONSTS] */
#define FUR_MAX_BATCH_SIZE 8192
#define FUR_MAX_BUFFER_SIZE FUR_MAX_BATCH_SIZE * sizeof(FURinstanceData)


#define FUR_genericInitEnd(name)        \
        void name##_init();             \
        void name##_end();              \
        void name##_draw();

        FUR_genericInitEnd(r2dRect);
        FUR_genericInitEnd(r2dTex);
        FUR_genericInitEnd(rSsCube);
        FUR_genericInitEnd(rSsModel);

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
