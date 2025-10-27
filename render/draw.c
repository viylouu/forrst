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

void fur_render_flush(FUR_renderState* render) {
    switch(render->api) {
        case FUR_RENDER_API_GL:
            fur_render_gl_flush(render->spec); break;
        warn_def_for("fur_render_flush");
    }
}

/* ====== FUNCS ====== */

void IMPL_fur_render_rect(FUR_renderState* render, OP_fur_render_rect op) {
    switch(render->api) {
        case FUR_RENDER_API_GL:
            fur_render_gl_rect(render->spec, op.target, op.transf, op.pos, op.size, op.col); break;
        warn_def_for("fur_render_rect");
    }
}

void IMPL_fur_render_tex(FUR_renderState* render, OP_fur_render_tex op) {
    if (op.texture) {
        if (!IS_NAN(op.sample.x)) op.sample.x /= op.texture->width;     else op.sample.x = 0;
        if (!IS_NAN(op.sample.y)) op.sample.y /= op.texture->height;    else op.sample.y = 0;
        if (!IS_NAN(op.sample.z)) op.sample.z /= op.texture->width;     else op.sample.z = 1;
        if (!IS_NAN(op.sample.w)) op.sample.w /= op.texture->height;    else op.sample.w = 1;
    } else {
        op.texture = render->nil;
        op.sample = (v4){0,0,1,1};
    }

    if (IS_NAN(op.size.x)) op.size.x = op.texture->width;
    if (IS_NAN(op.size.y)) op.size.y = op.texture->height;

    switch (render->api) {
        case FUR_RENDER_API_GL:
            fur_render_gl_tex(render->spec, op.target, op.texture, op.transf, op.pos, op.size, op.sample, op.col); break;
        warn_def_for("fur_render_tex");
    }
}
