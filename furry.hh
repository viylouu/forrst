#ifndef FUR_FURRY_HH
#define FUR_FURRY_HH

#include <core/macros.h>
#include <core/render.hh>
#include <core/auto/load_gl.h>
#include <core/node.hh>
#include <GLFW/glfw3.h>
#include <core/editor/editor.hh>
#include <core/text.hh>
#include <core/state.hh>

namespace fur {
    class Program {
    public:
        Node* scene;
        State* st;

        Program(State* state) { st = state; scene = new Node(); scene->name = (char*)"scene"; scene->editor_open = 1; }
        virtual ~Program() {}

        virtual void update(f32 delta) {}
        virtual void render()          {}
    };

    template<typename Tprogram>
    s32 windowDoShit(const char* title, v2 dims) {
        State* st = new State(title, dims.x, dims.y);
        st->glfwSetPtr(st);

        glViewport(0,0,dims.x,dims.y);

#ifdef _WIN32
        glfwSetWindowSize((GLFWwindow*)st->window, dims.x+1,dims.y+1);
        glfwSetWindowSize((GLFWwindow*)st->window, dims.x,dims.y);
#endif

        #ifdef FUR_EDITOR
        b8 editorOn = 1;
        Editor* editor = new Editor(st->render, st->text, st->input);
        #endif

        Tprogram* game = new Tprogram(st);
        game->scene->recinit();

        f32 lasttime = glfwGetTime();

        while (!st->shouldClose()) {
            st->poll();

            st->time = glfwGetTime();
            st->delta = st->time - lasttime;
            lasttime = glfwGetTime();

            st->width = st->render->width;
            st->height = st->render->height;

            game->update(st->delta);
            game->scene->recupdate(st->delta);

            game->render();
            game->scene->recrender();

            #ifdef FUR_EDITOR
            if (st->input->isKeyPressed(GLFW_KEY_F1))
                editorOn = !editorOn;

            if(editorOn)
                editor->main(st->width, st->height, game->scene);
            #endif

            st->render->flush();

            st->swapBuffer();
        }

        game->scene->recend();
        delete game->scene;
        delete game;

        #ifdef FST_EDITOR
        delete editor;
        #endif

        delete st;
        return 0;
    }
}

#endif
