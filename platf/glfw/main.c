#include "main.h"

#include <core/macros.h>
#include <stdio.h>
#include <stdlib.h>

#include <GLFW/glfw3.h>

/* ====== FUNCS ====== */

void fur_platf_glfw_constr(FUR_glfw_platfState* state, const char* title, s32 width, s32 height) {
    glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);
    glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_API);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GLFW_TRUE);

    ERROR_IF(!glfwInit(), "failed to init glfw!\n");

    state->window = glfwCreateWindow(width, height, title, NULL,NULL);

    glfwMakeContextCurrent(state->window);
}

void fur_platf_glfw_destr(FUR_glfw_platfState* state) {
    glfwDestroyWindow(state->window);
    glfwTerminate();
}
