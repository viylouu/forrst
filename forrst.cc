#include "forrst.hh"

#include <GLFW/glfw3.h>

#include <core/auto/load_gl.h>
#include <core/render.hh>

void fst_cb_size(GLFWwindow* window, s32 width, s32 height) {
    glViewport(0,0,width,height);
    void* state = glfwGetWindowUserPointer(window);
    if (state)
        fst_render_resize(state,width,height);
}

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

    glfwSwapInterval(0);

    return window;
}

char fst_shouldClose(void* state) {
    GLFWwindow* window = (GLFWwindow*)state;
    return glfwWindowShouldClose(window);
}

void fst_poll(void* state) {
    UNUSED(state);

    glfwPollEvents();
}

void fst_swapBuffer(void* state) {
    GLFWwindow* window = (GLFWwindow*)state;
    glfwSwapBuffers(window);
}

void fst_end(void* state) {
    GLFWwindow* window = (GLFWwindow*)state;

    glfwPollEvents(); // fix for segfault on crash for some reason? idk, glfw is weird

    glfwDestroyWindow(window);
    glfwTerminate();
}

