#ifndef FUR_STATE_HH
#define FUR_STATE_HH

#include <core/render.hh>
#include <core/text.hh>
#include <GLFW/glfw3.h>

namespace fur {
    class State {
    public:
        Render* render;
        Text* text;

        f32 time;
        f32 delta;

        const char* title;
        s32 width;
        s32 height;

        GLFWwindow* window;

    private:
        void init();
        void end();
        static void cb_size(GLFWwindow* window, s32 width, s32 height);

    public:
        State(const char* title, s32 width, s32 height);
        ~State();

        void glfwSetPtr(fur::State* state);

        b8 shouldClose();
        void poll();
        void swapBuffer();
    };
}

#endif
