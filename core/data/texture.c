#include "texture.h"

#include <core/data/api/gl/texture.h>

#include <render/state.h>
#include <core/macros.h>
#include <stdlib.h>
#include <stdio.h>

/* ====== FUNCS ====== */

FUR_texture* fur_texture_load(FUR_targetRenderApi api, const char* path) {
    // for now (void)path to make the compiler fucking shut up
    (void)path;

    FUR_texture* texture = NEW(FUR_texture);

    switch (api) {
        case FUR_RENDER_API_GL:
            texture->spec = fur_gl_texture_load(texture, path); break;
        warn_def_for("fur_texture_load");
    }

    return texture;
}

void fur_texture_unload(FUR_targetRenderApi api, FUR_texture* texture) {
    switch(api) {
        case FUR_RENDER_API_GL:
            fur_gl_texture_unload(texture->spec); break;
        warn_def_for("fur_texture_unload");
    }

    free(texture);
}
