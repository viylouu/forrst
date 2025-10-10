#ifndef FUR_TEXTURE_H
#define FUR_TEXTURE_H

#include <core/macros.h>

namespace fur {
    struct Texture {
        u32 glid;
        s32 width;
        s32 height;
    };

    namespace texture {
        void     unload(Texture* tex);
        Texture* make(s32 width, s32 height);
        Texture* loadFromData(u8* data, s64 size);
        char*    loadData(const char* path, s64* outsize);
        Texture* load(const char* path);
    }
}

#endif
