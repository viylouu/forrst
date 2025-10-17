#ifndef FUR_RENDER_STATE_H
#define FUR_RENDER_STATE_H

/* ====== DATATYPES ====== */

    /* FUR_target_renderState union
     * pointer to the underlying api specific data
     * (not a pointer because i like typing TYPE*)
     * valid cases:
     * - FUR_gl_renderState
     */
typedef void FUR_target_renderState;

    /* FUR_targetRenderApi enum
     * enum for which render api is being used
     * stored in FUR_renderState
     */
typedef enum {
    FUR_RENDER_API_GL
} FUR_targetRenderApi;

    /* FUR_renderState struct
     * holds the api agnostic data
     * aswell as the specific data (stored as a FUR_target_renderState)
     */
typedef struct {
    FUR_target_renderState* spec;
    FUR_targetRenderApi api;
} FUR_renderState;

#endif
