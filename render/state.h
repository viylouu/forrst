#ifndef FUR_RENDER_STATE_H
#define FUR_RENDER_STATE_H

#include <render/api.h>
#include <core/data/texture.h>

/* ====== DATATYPES ====== */

typedef void FUR_target_renderState;

typedef struct {
    FUR_target_renderState* spec;
    FUR_targetRenderApi api;
    FUR_texture* nil;
    s32 width;
    s32 height;
} FUR_renderState;

#endif
