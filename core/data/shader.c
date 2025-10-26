#include "shader.h"

#include <core/macros.h>
#include <stdlib.h>
#include <stdio.h>
#include <render/state.h>

#include <core/data/api/gl/shader.h>

/* ====== FUNCS ====== */

FUR_shader* IMPL_fur_shader_load(const char* vert, const char* frag, OP_fur_shader_GENERIC op) {
    FUR_shader* shader = NEW(FUR_shader);

    switch (op.api) {
        case FUR_RENDER_API_GL:
            shader->spec = fur_gl_shader_load(shader, vert, frag); break;
        warn_def_for("fur_shader_load");
    }

    return shader;
}

void IMPL_fur_shader_unload(FUR_shader* shader, OP_fur_shader_GENERIC op) {
    switch (op.api) {
        case FUR_RENDER_API_GL:
            fur_gl_shader_unload(shader->spec); break;
        warn_def_for("fur_shader_unload");
    }

    free(shader);
}
