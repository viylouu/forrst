#ifndef FUR_TEXTURE_H
#define FUR_TEXTURE_H

#include <core/macros.h>
#include <render/api.h>

/* ====== DATATYPES ====== */

typedef void FUR_apiTexture;

typedef struct {
    FUR_apiTexture* spec;
    s32 width, height;
} FUR_texture;

/* ====== DATATYPES ====== */

typedef struct {
    FUR_targetRenderApi api;
} OP_fur_texture_GENERIC;

/* ====== FUNCS ====== */

FUR_texture* IMPL_fur_texture_load(const char* path, OP_fur_texture_GENERIC op);
void IMPL_fur_texture_unload(FUR_texture* texture, OP_fur_texture_GENERIC op);

/* ====== MACROS ====== */

#define fur_texture_load(path, ...) \
    IMPL_fur_texture_load((path), (OP_fur_texture_GENERIC){ .api = FUR_RENDER_API_GL, __VA_ARGS__ })

#define fur_texture_unload(texture, ...) \
    IMPL_fur_texture_unload((texture), (OP_fur_texture_GENERIC){ .api = FUR_RENDER_API_GL, __VA_ARGS__ })

#endif
