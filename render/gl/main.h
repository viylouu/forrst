#ifndef FUR_RENDER_GL_MAIN_H
#define FUR_RENDER_GL_MAIN_H

#include <core/macros.h>
#include <render/state.h>

/* ====== STRUCTS ====== */

    /* FUR_gl_renderState struct
     * holds the opengl api's render state data
     */
typedef struct {
    FUR_renderState* agnostic;
    u32 shitty_vao;
} FUR_gl_renderState;

/* ====== FUNCS ====== */

    /* fur_render_gl_constr func
     * constructs and returns a FUR_gl_renderState
     *
     * params:
     *  - FUR_renderState* agnostic -- the input agnostic render state
     */
FUR_gl_renderState* fur_render_gl_constr(FUR_renderState* agnostic);

    /* fur_render_gl_destr func
     * destructs the input gl render state
     *
     * state requires:
     *  - to have been constructed
     *
     * params
     * - FUR_gl_renderState* state -- the input gl render state
      */
void fur_render_gl_destr(FUR_gl_renderState* state);

#endif
