#ifndef FUR_SHADER_H
#define FUR_SHADER_H

#include <core/macros.h>
#include <render/state.h>

/* ====== DATATYPES ====== */

typedef void FUR_apiShader;

typedef struct {
    FUR_apiShader* spec;
} FUR_shader;

/* ====== DATATYPES ====== */

typedef struct {
    FUR_targetRenderApi api;
} OP_fur_shader_GENERIC;

/* ====== FUNCS ====== */

FUR_shader* IMPL_fur_shader_load(const char* vert, const char* frag, OP_fur_shader_GENERIC op);
void IMPL_fur_shader_unload(FUR_shader* shader, OP_fur_shader_GENERIC op);

/* ====== MACROS ====== */

#define fur_shader_load(vert, frag, ...) \
    IMPL_fur_shader_load((vert), (frag), (OP_fur_shader_GENERIC){ .api = FUR_RENDER_API_GL, __VA_ARGS__ })

#define fur_shader_unload(shader, ...) \
    IMPL_fur_shader_unload((shader), (OP_fur_shader_GENERIC){ .api = FUR_RENDER_API_GL, __VA_ARGS__ })

#endif
