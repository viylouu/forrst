#ifndef FUR_FURRY_HH
#define FUR_FURRY_HH

#include <core/macros.h>
#include <core/render.hh>
#include <core/auto/load_gl.h>
#include <core/node.hh>
#include <GLFW/glfw3.h>
#include <core/editor/editor.hh>

namespace fur {
    class State;
    class State {
    public:
        const Render* render;

        f32 time;
        f32 delta;

        const char* title;
        s32 width;
        s32 height;

    private:
        GLFWwindow* window;

    private:
        void init();
        void end();
        void cb_size(GLFWwindow* window, s32 width, s32 height);

    public:
        State(const char* title, s32 width, s32 height);
        ~State();

        void glfwSetPtr(fur::State* state);

        b8 shouldClose();
        void poll();
        void swapBuffer();
    };

    class Program {
    public:
        Node* scene;

        Program(const fur::State* state) {}

        virtual void init()            {}
        virtual void update(f32 delta) {}
        virtual void render()          {}
        virtual void end()             {}
    };

    template<typename Tprogram>
    s32 windowDoShit(const char* title, v2 dims);

#define FUR_MAIN(class)                                            \
    int main(void) {                                               \
        return fur::windowDoShit<class>("title", ((v2){800,600})); \
    }

}

#endif
