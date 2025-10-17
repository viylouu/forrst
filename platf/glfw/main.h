#ifndef FUR_PLATFORM_GLFW_H
#define FUR_PLATFORM_GLFW_H

#include <core/macros.h>
#include <GLFW/glfw3.h>
#include <platf/state.h> // ts pmo

/* ====== STRUCTS ====== */

    /* FUR_gl_renderState struct
     * holds the opengl api's render state data
     */
typedef struct {
    FUR_platfState* agnostic;
    GLFWwindow* window;
} FUR_glfw_platfState;

/* ====== FUNCS ====== */

    /* fur_platf_glfw_constr func
     * constructs and returns a glfw platform state
     *
     * params:
     *  - FUR_platfState* agnostic -- the input agnostic platform state
     */
FUR_glfw_platfState* fur_platf_glfw_constr(FUR_platfState* agnostic);

    /* fur_platf_glfw_destr func
     * destructs the input glfw platform state
     *
     * state requires:
     *  - to have been constructed
     *
     * params
     *  - FUR_glfw_platfState* state -- the input glfw platform state
     */
void fur_platf_glfw_destr(FUR_glfw_platfState* state);

    /* fur_platf_glfw_shouldWindowClose func
     * returns if the window should store processing events
     *
     * state requires:
     *  - to have been constructed
     *
     * params
     *  - FUR_glfw_platfState* state -- the input glfw platform state
     */
b8 fur_platf_glfw_shouldWindowClose(FUR_glfw_platfState* state);

    /* fur_platf_glfw_poll func
     * grabs input events
     *
     * state requires:
     *  - to have been constructed
     *
     * params
     *  - FUR_glfw_platfState* state -- the input platform state
     */
void fur_platf_glfw_poll(FUR_glfw_platfState* state);

    /* fur_platf_glfw_present func
     * presents/swaps the current window's buffer
     *
     * state requires:
     *  - to have been constructed
     *
     * params
     *  - FUR_platfState* state -- the input platform state
     *
     * must be called after fur_platf_constr has been called
     */
void fur_platf_glfw_present(FUR_glfw_platfState* state);

#endif
