#ifndef FUR_TEXTURE_H
#define FUR_TEXTURE_H

#include <core/macros.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
    u32 glid;
    s32 width;
    s32 height;
} FURtexture;

void fur_texture_unload(FURtexture* tex);
FURtexture* fur_texture_make(s32 width, s32 height);
FURtexture* fur_texture_loadFromData(u8* data, s64 size);
char* fur_texture_loadData(const char* path, s64* outsize);
FURtexture* fur_texture_load(const char* path);

#ifdef __cplusplus
}
#endif

#endif
