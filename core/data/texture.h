#ifndef FUR_TEXTURE_H
#define FUR_TEXTURE_H

/* ====== DATATYPES ====== */

typedef void FUR_apiTexture;

typedef struct {
    FUR_apiTexture* spec;
} FUR_texture;

/* ====== FUNCS ====== */

FUR_texture* fur_texture_load(const char* path);
void fur_texture_unload(FUR_texture* texture);

#endif
