#include "draw.h"

#include <render/gl/draw.h>

#include <render/state.h>
#include <core/macros.h>
#include <stdio.h>

/* ====== FUNCS ====== */

void fur_render_clear(FUR_renderState* render, f32 r, f32 g, f32 b) {
    switch(render->api) {
        case FUR_RENDER_API_GL:
            fur_render_gl_clear(render->spec, r,g,b); break;
        warn_def_for("fur_render_clear");
    }
}
