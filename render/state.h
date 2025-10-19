#ifndef FUR_RENDER_STATE_H
#define FUR_RENDER_STATE_H

/* ====== DATATYPES ====== */

typedef void FUR_target_renderState;

typedef enum {
    FUR_RENDER_API_GL
} FUR_targetRenderApi;

typedef struct {
    FUR_target_renderState* spec;
    FUR_targetRenderApi api;
} FUR_renderState;

#endif
