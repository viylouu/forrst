#include "forrst.h"

#include <GLFW/glfw3.h>

#include <core/load_gl.h>
#include <core/render.h>

void* fst_init(const char* title, s32 width, s32 height) {
    glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);
    glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_API);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    ERROR_IF(!glfwInit(), "failed to init opengl!\n");

    GLFWwindow* window = glfwCreateWindow(width, height, title, NULL,NULL);
    ERROR_IF(!window, "failed to make glfw window!\n");

    glfwMakeContextCurrent(window);

    fst_use_wayland = glfwGetPlatform() == GLFW_PLATFORM_WAYLAND;

    return window;
}

char fst_shouldClose(void* state) {
    GLFWwindow* window = state;
    return glfwWindowShouldClose(window);
}

void fst_poll(void* state) {
    UNUSED(state);

    glfwPollEvents();
}

void fst_swapBuffer(void* state) {
    GLFWwindow* window = state;
    glfwSwapBuffers(window);
}

void fst_end(void* state) {
    GLFWwindow* window = state;

    glfwPollEvents(); // fix for segfault on crash for some reason? idk, glfw is weird

    glfwDestroyWindow(window);
    glfwTerminate();
}

s32 EXPLICIT_fst_windowDoShit(const char* title, v2 dims, FSTwindowDoShitOPS ops) {
    UNUSED(ops);

    void* state = fst_init(title, dims.x,dims.y);
    void* rstate = fst_render_init();

    fst_gl_load();

    MAYBE_CALL(ops.init);

    while (!fst_shouldClose(state)) {
        fst_poll(state);

        MAYBE_CALL(ops.update);
        MAYBE_CALL(ops.render);

        fst_swapBuffer(state);
    }

    MAYBE_CALL(ops.end);

    fst_render_end(rstate);
    fst_end(state);
    return 0;
}
