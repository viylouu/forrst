#include "furry.hh"

#include <GLFW/glfw3.h>

#include <core/auto/load_gl.h>
#include <core/render.hh>

void fur_cb_size(GLFWwindow* window, s32 width, s32 height) {
    
}

void* fur_init(const char* title, s32 width, s32 height) {
   }

char fur_shouldClose(void* state) {
    GLFWwindow* window = (GLFWwindow*)state;
    return glfwWindowShouldClose(window);
}

void fur_poll(void* state) {
    UNUSED(state);

    glfwPollEvents();
}

void fur_swapBuffer(void* state) {
    GLFWwindow* window = (GLFWwindow*)state;
    glfwSwapBuffers(window);
}

void fur_end(void* state) {
    
}

