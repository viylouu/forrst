#include <GLFW.h>

#include <stdio.h>
#include <stdlib.h>

int main(void) {

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

    while(!glfwWindowShouldClose(window)) {
        glfwPollEvents();
        glfwSwapBuffers(window);
    }

    glfwPollEvents(); // fix for segfault on crash for some reason? idk, glfw is weird

    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}
