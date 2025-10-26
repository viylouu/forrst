#include "texture.h"

#include <core/data/api/gl/texture.h>

#include <render/state.h>
#include <core/macros.h>
#include <stdlib.h>
#include <stdio.h>

/* ====== FUNCS ====== */

FUR_texture* IMPL_fur_texture_load(const char* path, OP_fur_texture_GENERIC op) {
    // for now (void)path to make the compiler fucking shut up
    (void)path;

    FUR_texture* texture = NEW(FUR_texture);

    switch (op.api) {
        case FUR_RENDER_API_GL:
            texture->spec = fur_gl_texture_load(texture, path); break;
        warn_def_for("fur_texture_load");
    }

    return texture;
}

void IMPL_fur_texture_unload(FUR_texture* texture, OP_fur_texture_GENERIC op) {
    switch(op.api) {
        case FUR_RENDER_API_GL:
            fur_gl_texture_unload(texture->spec); break;
        warn_def_for("fur_texture_unload");
    }

    TRY_FREE(texture);
}
