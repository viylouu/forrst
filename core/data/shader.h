#ifndef FUR_SHADER_H
#define FUR_SHADER_H

#include <core/macros.h>

/* ====== DATATYPES ====== */

typedef void FUR_apiShader;

typedef struct {
    FUR_apiShader* spec;
} FUR_shader;

/* ====== FUNCS ====== */

FUR_shader* fur_shader_load(const char* vert, const char* frag);
void fur_shader_unload(FUR_shader* shader);

#endif
