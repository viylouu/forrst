#define RGFW_IMPLEMENTATION
#define RGFW_ALLOC_DROPFILES
#define RGFW_OPENGL
#define RGFW_PRINT_ERRORS
#define RGFW_DEBUG
#define GL_SILENCE_DEPTRECATION
#include <RGFW.h>

#include <GLES3/gl3.h>

#define RGL_LOAD_IMPLEMENTATION
#include "rglLoad.h"

#include <stdio.h>

int main(void) {
    RGFW_glHints* hints = RGFW_getGlobalHints_OpenGL();
    hints->major = 3;
    hints->minor = 3;
    RGFW_setGlobalHints_OpenGL(hints);
    
    RGFW_window* window = RGFW_createWindow("opengl", 800, 600, 800, 600, RGFW_windowAllowDND | RGFW_windowCenter | RGFW_windowScaleToMonitor | RGFW_windowOpenGL);
    if (!window) {
        printf("failed to create rgfw window!\n");
        exit(1);
    }
    RGFW_window_setExitKey(window, RGFW_escape);
    RGFW_window_makeCurrentContext_OpenGL(window);

    if (RGL_loadGL3((RGLloadfunc)RGFW_getProcAddress_OpenGL)) {
        printf("failed to init GLAD!\n");
        exit(1);
    }

    while(RGFW_window_shouldClose(window) == RGFW_FALSE) {
        RGFW_event event;

        while (RGFW_window_checkEvent(window, &event)) {
            if (event.type == RGFW_quit) {
                break;
            }
        }

        glClearColor(.2f,.3f,.3f,1);
        glClear(GL_COLOR_BUFFER_BIT);

        RGFW_window_swapBuffers_OpenGL(window);
    }

    RGFW_window_close(window);
    return 0;
}
