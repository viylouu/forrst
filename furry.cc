#include "furry.hh"

#include <GLFW/glfw3.h>

#include <core/auto/load_gl.h>
#include <core/render.hh>

namespace fur {
    void State::init() {
        glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);
        glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_API);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

        ERROR_IF(!glfwInit(), "failed to init glfw!\n");

        window = glfwCreateWindow(width, height, title, NULL,NULL);
        ERROR_IF(!window, "failed to make glfw window!\n");

        glfwMakeContextCurrent(window);

        fur_use_wayland = glfwGetPlatform() == GLFW_PLATFORM_WAYLAND;   

        glfwSwapInterval(0);

        fur_gl_load();

        render = new fur::Render();
    }

    void State::end() {
        glfwPollEvents(); // fix for segfault on crash for some reason? idk, glfw is weird

        glfwDestroyWindow(window);
        glfwTerminate();
    }

    void State::cb_size(GLFWwindow* window, s32 width, s32 height) {
        glViewport(0,0,width,height);
        void* st = glfwGetWindowUserPointer(window);
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

    b8   State::shouldClose() {}
    void State::poll() {}
    void State::swapBuffer() {}

    /*
     *
     */

    template<typename Tprogram>
    s32 windowDoShit(const char* title, v2 dims) {
        State* st = new State();
        st->glfwSetPtr(st);

        //void* state = fur::init(title, dims.x,dims.y);
        //fur_gl_load();
        //void* rstate = fur_render_init();

        //glfwSetWindowUserPointer((GLFWwindow*)state, rstate);
        //glfwSetFramebufferSizeCallback((GLFWwindow*)state, fur::cb_size);

        glViewport(0,0,dims.x,dims.y);

#ifdef _WIN32
        glfwSetWindowSize((GLFWwindow*)state, dims.x+1,dims.y+1);
        glfwSetWindowSize((GLFWwindow*)state, dims.x,dims.y);
#endif

        #ifdef FUR_EDITOR
        b8 editor = 1;
        b8 prevKey = 0;
        void* estate = fur_editor_init();
        #endif

        Tprogram* game = new Tprogram(st);

        game->scene = new FURnode();
        game->scene->name = "scene";

        f32 lasttime = glfwGetTime();

        while (!st->shouldClose()) {
            st->poll();

            st->time = glfwGetTime();
            st->delta = st->time - lasttime;
            lasttime = glfwGetTime();

            game->update(st->delta);
            game->scene->recupdate(st->delta);

            game->render();
            game->scene->recrender();

            #ifdef FUR_EDITOR
            b8 curKey = glfwGetKey((GLFWwindow*)state, GLFW_KEY_F1);
            if (curKey == GLFW_PRESS && prevKey == GLFW_RELEASE)
                editor = !editor;
            prevKey = curKey;

            if(editor)
                fur_editor(estate, state, rstate, game.scene);
            #endif

            st->render->flush();

            st->swapBuffer();
        }

        delete game->scene;
        delete game;

        #ifdef FST_EDITOR
        fur_editor_end(estate);
        #endif

        delete st;
        return 0;
    }

    template s32 windowDoShit<Program>(const char* title, v2 dims);
}
