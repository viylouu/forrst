#ifndef FUR_TEXTURE_H
#define FUR_TEXTURE_H

#include <core/macros.h>
#include <render/state.h>

/* ====== DATATYPES ====== */

typedef void FUR_apiTexture;

typedef struct {
    FUR_apiTexture* spec;
    s32 width, height;
} FUR_texture;

/* ====== FUNCS ====== */

FUR_texture* fur_texture_load(FUR_targetRenderApi api, const char* path);
void fur_texture_unload(FUR_targetRenderApi api, FUR_texture* texture);

#endif
