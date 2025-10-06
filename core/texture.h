#ifndef FST_TEXTURE_H
#define FST_TEXTURE_H

#include <core/macros.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
    u32 glid;
    s32 width;
    s32 height;
} FSTtexture;

void fst_texture_unload(FSTtexture* tex);
FSTtexture* fst_texture_loadFromData(u8* data, s64 size);
char* fst_texture_loadData(const char* path, s64* outsize);
FSTtexture* fst_texture_load(const char* path);

#ifdef __cplusplus
}
#endif

#endif
