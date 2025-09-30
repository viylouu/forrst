#include <GLFW.h>

#include <stdio.h>
#include <stdlib.h>


void* fst_init(void) {
    glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);
    glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_API);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);;
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    if (!glfwInit()) {
        printf("failed to init opengl!\n");
        exit(1);
    }

    GLFWwindow* window = glfwCreateWindow(800, 600, "title", NULL,NULL);
    if (!window) {
        printf("failed to make glfw window!\n");
        exit(1);
    }

    glfwMakeContextCurrent(window);

    return window;
}

char fst_shouldClose(void* state) {
    GLFWwindow* window = state;
    return glfwWindowShouldClose(window);
}

void fst_poll(void* state) {
    (void)state;

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



int main(void) {
    void* state = fst_init();

    while (!fst_shouldClose(state)) {
        fst_poll(state);
        fst_swapBuffer(state);
    }

    fst_end(state);
    return 0;
}
