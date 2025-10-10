#include "furry.hh"

#include <GLFW/glfw3.h>
#include <core/auto/load_gl.h>
#include <core/render.hh>
#include <core/text.hh>
#include <core/editor/editor.hh>

namespace fur {
    void State::init() {
        glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);
        glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_API);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GLFW_TRUE);

        ERROR_IF(!glfwInit(), "failed to init glfw!\n");

        window = glfwCreateWindow(width, height, title, NULL,NULL);
        ERROR_IF(!window, "failed to make glfw window!\n");

        glfwMakeContextCurrent(window);

        fur_use_wayland = glfwGetPlatform() == GLFW_PLATFORM_WAYLAND;   

        glfwSwapInterval(0);

        fur_gl_load();

        render = new Render();
        text = new Text(render);
    }

    void State::end() {
        glfwPollEvents(); // fix for segfault on crash for some reason? idk, glfw is weird

        glfwDestroyWindow(window);
        glfwTerminate();
    }

    void State::cb_size(GLFWwindow* window, s32 width, s32 height) {
        glViewport(0,0,width,height);
        State* st = (State*)glfwGetWindowUserPointer(window);
        if (st)
            st->render->resize(width,height);           
    }

    /*
     *
     */

    State::State(const char* title, s32 width, s32 height) {
        this->title  = title;
        this->width  = width;
        this->height = height;

        init();
    }

    State::~State() {
        end();
    }

    void State::glfwSetPtr(fur::State* state) { 
        glfwSetWindowUserPointer(window, state); 
    }

    b8   State::shouldClose() { return glfwWindowShouldClose(window); }
    void State::poll() { glfwPollEvents(); }
    void State::swapBuffer() { glfwSwapBuffers(window); }   
}
