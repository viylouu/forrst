#include "renderTarget.h"

#include <core/macros.h>
#include <stdlib.h>
#include <stdio.h>

/* ====== FUNCS ====== */

FUR_renderTarget* IMPL_fur_renderTarget_constr(s32 width, s32 height, OP_fur_renderTarget_constr op) {
    FUR_renderTarget* targ = NEW(FUR_renderTarget);
    targ->width = width;
    targ->height = height;
    targ->api = op.api;

    switch (op.api) {
        case FUR_RENDER_API_GL:
        warn_def_for("fur_renderTarget_constr");
    }

    return targ;
}

void fur_renderTarget_destr(FUR_renderTarget* targ) {
    switch (targ->api) {
        warn_def_for("fur_renderTarget_constr");
    }

    free(targ);
}
