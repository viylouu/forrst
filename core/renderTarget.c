#include "renderTarget.h"

#include <core/render/gl/renderTarget.h>

#include <core/macros.h>
#include <stdlib.h>
#include <stdio.h>

/* ====== FUNCS ====== */

FUR_renderTarget* IMPL_fur_renderTarget_constr(s32 width, s32 height, OP_fur_renderTarget_constr op) {
    FUR_renderTarget* targ = NEW(FUR_renderTarget);
    targ->api = op.api;

    FUR_texture* tex = NEW(FUR_texture);
    tex->width = width;
    tex->height = height;
    tex->spec = NULL;

    targ->texture = tex;

    switch (op.api) {
        case FUR_RENDER_API_GL:
            targ->spec = fur_renderTarget_gl_constr(targ, width, height); break;
        warn_def_for("fur_renderTarget_constr");
    }

    return targ;
}

void fur_renderTarget_destr(FUR_renderTarget* targ) {
    switch (targ->api) {
        case FUR_RENDER_API_GL:
            fur_renderTarget_gl_destr(targ->spec); break;
        warn_def_for("fur_renderTarget_constr");
    }

    free(targ);
}

void fur_renderTarget_resize(FUR_renderTarget* targ, s32 width, s32 height) {
    targ->texture->width = width;
    targ->texture->height = height;

    switch (targ->api) {
        case FUR_RENDER_API_GL:
            fur_renderTarget_gl_resize(targ->spec, width, height); break;
        warn_def_for("fur_renderTarget_resize");
    }
}
