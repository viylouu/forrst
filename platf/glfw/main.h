#ifndef FUR_PLATFORM_GLFW_H
#define FUR_PLATFORM_GLFW_H

#include <core/macros.h>
#include <GLFW/glfw3.h>
#include <platf/state.h> // ts pmo
#include <render/state.h>

/* ====== STRUCTS ====== */

typedef struct {
    FUR_platfState* agnostic;
    GLFWwindow* window;
} FUR_glfw_platfState;

/* ====== FUNCS ====== */

FUR_glfw_platfState* fur_platf_glfw_constr(FUR_platfState* agnostic);
void fur_platf_glfw_destr(FUR_glfw_platfState* state);

b8 fur_platf_glfw_shouldWindowClose(FUR_glfw_platfState* state);

void fur_platf_glfw_poll(FUR_glfw_platfState* state);

void fur_platf_glfw_present(FUR_glfw_platfState* state);

void fur_platf_glfw_setRender(FUR_glfw_platfState* state, FUR_renderState* render);

#endif
