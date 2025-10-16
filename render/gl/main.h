#ifndef FUR_RENDER_GL_MAIN_H
#define FUR_RENDER_GL_MAIN_H

#include <core/macros.h>

/* ====== STRUCTS ====== */

    /* FUR_gl_renderState struct
     * holds the opengl api's render state data
     */
typedef struct {
    s32 pretend_somethings_here;
} FUR_gl_renderState;

/* ====== FUNCS ====== */

    /* fur_render_gl_constr func
     * creates/initializes the input gl render state
     *
     * params:
     *  - FUR_gl_renderState* state -- the input gl render state
     * 
     * input gl render state must be created manually
*** USAGE ***
FUR_gl_renderState* state = NEW(FUR_gl_renderState);
fur_render_gl_constr(&state);
*** ***** ***
     */
void fur_render_gl_constr(FUR_gl_renderState* state);

    /* fur_render_gl_destr func
     * ends/destroys the input gl render state
     *
     * params
     * - FUR_gl_renderState* state -- the input gl render state
     *
     * input gl render state must be created manually
     * must be called after fur_render_gl_init has been called
*** USAGE ***
FUR_gl_renderState* state = NEW(FUR_gl_renderState);
fur_render_gl_constr(&state);
// do something
fur_render_gl_destr(&state);
*** ***** ***
     */
void fur_render_gl_destr(FUR_gl_renderState* state);

#endif
