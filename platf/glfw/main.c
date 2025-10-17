#include "main.h"

#include <core/macros.h>
#include <stdio.h>
#include <stdlib.h>
#include <GLFW/glfw3.h>

/* ====== FUNCS ====== */

FUR_glfw_platfState* fur_platf_glfw_constr(FUR_platfState* agnostic) {
    FUR_glfw_platfState* state = NEW(FUR_glfw_platfState);
    state->agnostic = agnostic;

    glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);
    glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_API);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GLFW_TRUE);

    ERROR_IF(!glfwInit(), "failed to init glfw!\n");

    state->window = glfwCreateWindow(state->agnostic->width, state->agnostic->height, state->agnostic->title, NULL,NULL);

    glfwMakeContextCurrent(state->window);

    return state;
}

void fur_platf_glfw_destr(FUR_glfw_platfState* state) {
    glfwDestroyWindow(state->window);
    glfwTerminate();

    free(state);
}

b8 fur_platf_glfw_shouldWindowClose(FUR_glfw_platfState* state) {
    return glfwWindowShouldClose(state->window);
}

void fur_platf_glfw_poll(FUR_glfw_platfState* state) {
    (void)state;

    glfwPollEvents();
}

void fur_platf_glfw_present(FUR_glfw_platfState* state) {
    glfwSwapBuffers(state->window);
}
