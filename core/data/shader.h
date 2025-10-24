#ifndef FUR_SHADER_H
#define FUR_SHADER_H

#include <core/macros.h>
#include <render/state.h>

/* ====== DATATYPES ====== */

typedef void FUR_apiShader;

typedef struct {
    FUR_apiShader* spec;
} FUR_shader;

/* ====== FUNCS ====== */

FUR_shader* fur_shader_load(FUR_targetRenderApi api, const char* vert, const char* frag);
void fur_shader_unload(FUR_targetRenderApi api, FUR_shader* shader);

#endif
