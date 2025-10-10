#ifndef FUR_RENDER_HH
#define FUR_RENDER_HH

#include <core/macros.h>
#include <core/shader.hh>
#include <core/texture.hh>
#include <core/mat4.h>

namespace fur {
    class Render;
    class Render {
public:
        /* table of contents:
         **** [CONSTS]
         **** [GL STRUCTS]
         **** **** [gl struct 2d]
         **** **** [gl struct spritestack]
         **** [some shi]
         **** [STATE]
         **** [INIT/END]
         **** [UPDATE]
         **** [FUNCS]
         */

        /* [CONSTS] */
#define FUR_MAX_BATCH_SIZE 8192
#define FUR_MAX_BUFFER_SIZE FUR_MAX_BATCH_SIZE * sizeof(FURinstanceData)

        /*
         * [INIT/END]
         */

        Render();
        ~Render();

        /*
         * [UPDATE]
         */

        void resize(void* data, s32 width, s32 height);

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
