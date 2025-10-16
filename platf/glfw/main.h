#ifndef FUR_PLATFORM_GLFW_H
#define FUR_PLATFORM_GLFW_H

#include <core/macros.h>
#include <GLFW/glfw3.h>

/* ====== STRUCTS ====== */

    /* FUR_gl_renderState struct
     * holds the opengl api's render state data
     */
typedef struct {
    GLFWwindow* window;
} FUR_glfw_platfState;

/* ====== FUNCS ====== */

    /* fur_platf_glfw_constr func
     * constructs the input glfw platform state
     *
     * params:
     *  - FUR_glfw_platfState* state -- the input glfw platform state
     * 
     * input glfw platform state must be created manually
*** USAGE ***
FUR_glfw_platfState* state = NEW(FUR_glfw_platfState);
fur_platf_glfw_constr(&state);
*** ***** ***
     */
void fur_platf_glfw_constr(FUR_glfw_platfState* state, const char* title, s32 width, s32 height);

    /* fur_platf_glfw_destr func
     * destructs the input glfw platform state
     *
     * params
     * - FUR_glfw_platfState* state -- the input glfw platform state
     *
     * input glfw platform state must be created manually
     * must be called after fur_platform_glfw_init has been called
*** USAGE ***
FUR_glfw_platfState* state = NEW(FUR_glfw_platfState);
fur_platf_glfw_constr(&state);
// do something
fur_platf_glfw_destr(&state);
*** ***** ***
     */
void fur_platf_glfw_destr(FUR_glfw_platfState* state);

#endif
