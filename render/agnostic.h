#ifndef FUR_RENDER_AGNOSTIC_H
#define FUR_RENDER_AGNOSTIC_H

#include <render/gl/main.h>

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

/* ====== FUNCS ====== */

    /* fur_render_constr func
     * constructs the input render state
     *
     * params:
     *  - FUR_renderState* state -- the input render state
     * 
     * input render state must be created manually
*** USAGE ***
FUR_renderState* state = NEW(FUR_renderState);
state->api = ...
fur_render_constr(&state);
// do stuff
*** ***** ***
     */
void fur_render_constr(FUR_renderState* state);

    /* fur_render_destr func
     * destructs the input render state
     *
     * params
     * - FUR_renderState* state -- the input render state
     *
     * input render state must be created manually
     * must be called after fur_render_constr has been called
*** USAGE ***
FUR_renderState* state = NEW(FUR_renderState);
state->api = ...
fur_render_constr(&state);
// do something
fur_render_destr(&state);
*** ***** ***
     */
void fur_render_destr(FUR_renderState* state);

#endif
