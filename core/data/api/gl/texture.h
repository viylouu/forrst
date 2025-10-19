#ifndef FUR_GL_TEXTURE_H
#define FUR_GL_TEXTURE_H

#include <core/data/texture.h>
#include <core/macros.h>

/* ====== DATATYPES ====== */

typedef struct {
    FUR_texture* agnostic;
} FUR_gl_texture;

/* ====== FUNCS ====== */

FUR_gl_texture* fur_gl_texture_load(FUR_texture* agnostic, const char* path);
void fur_gl_texture_unload(FUR_gl_texture* texture);


#endif
