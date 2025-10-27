#ifndef FUR_RENDER_RENDER_TARGET_H
#define FUR_RENDER_RENDER_TARGET_H

#include <core/macros.h>
#include <render/api.h>

/* ====== DATATYPES ====== */

typedef void FUR_targetRenderTarget;

typedef struct {
    FUR_targetRenderTarget* spec;
    FUR_targetRenderApi api;

    s32 width, height;
} FUR_renderTarget;

/* ====== DATATYPES ====== */

typedef struct {
    FUR_targetRenderApi api;
} OP_fur_renderTarget_constr;

/* ====== FUNCS ====== */

FUR_renderTarget* IMPL_fur_renderTarget_constr(s32 width, s32 height, OP_fur_renderTarget_constr op); 
void fur_renderTarget_destr(FUR_renderTarget* targ);

void fur_renderTarget_resize(FUR_renderTarget* targ, s32 width, s32 height);

/* ====== MACROS ====== */

#define fur_renderTarget_constr(width, height, ...) \
    IMPL_fur_renderTarget_constr((width), (height), (OP_fur_renderTarget_constr){ .api = FUR_RENDER_API_GL, __VA_ARGS__ })

#endif
