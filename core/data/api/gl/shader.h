#ifndef FUR_GL_SHADER_H
#define FUR_GL_SHADER_H

#include <core/data/shader.h>
#include <core/macros.h>

/* ====== DATATYPES ====== */

typedef struct {
    FUR_shader* agnostic;

    u32 program;
} FUR_gl_shader;

/* ====== FUNCS ====== */

FUR_gl_shader* fur_gl_shader_load(FUR_shader* agnostic, const char* vert, const char* frag);
void fur_gl_shader_unload(FUR_gl_shader* shader);

#endif
