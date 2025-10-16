#ifndef FUR_RENDER_GL_MAIN_H
#define FUR_RENDER_GL_MAIN_H

    /* fur_render_constr func
     * creates/initializes the input render state
     *
     * params:
     *  - FUR_renderState* state -- the input render state
     * 
     * input render state must be created manually
*** USAGE ***
FUR_renderState* state = NEW(FUR_renderState);
fur_render_constr(&state);
*** ***** ***
     */
void fur_render_constr(FUR_gl_renderState* state);

    /* fur_render_destr func
     * ends/destroys the input render state
     *
     * params
     * - FUR_renderState* state -- the input render state
     *
     * input render state must be created manually
     * must be called after fur_render_init has been called
*** USAGE ***
FUR_renderState* state = NEW(FUR_renderState);
fur_render_constr(&state);
// do something
fur_render_destr(&state);
*** ***** ***
     */
void fur_render_constr(FUR_gl_renderState* state);

#endif
