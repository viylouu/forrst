#ifndef FRST_FORRST_HH
#define FRST_FORRST_HH

#include <core/macros.h>
#include <core/render.hh>
#include <core/auto/load_gl.h>
#include <core/node.hh>
#include <GLFW/glfw3.h>

void* fst_init(const char* title, s32 width, s32 height);
char fst_shouldClose(void* state);
void fst_poll(void* state);
void fst_swapBuffer(void* state);
void fst_end(void* state);

static void* rstate;
static f64 time;

class FSTgame {
public:
    FSTnode* scene;

    void constr()   { 
        scene = new FSTnode(); 
    }

    virtual void init()   {}
    virtual void update(f32 delta) {}
    virtual void render() {}
    virtual void end()    {}
};

template<typename Tgame>
s32 fst_windowDoShit(const char* title, v2 dims) {
    FSTgame* forcetype = static_cast<Tgame*>(0); (void)forcetype;

    void* state = fst_init(title, dims.x,dims.y);
    fst_gl_load();
    rstate = fst_render_init();

    glViewport(0,0,dims.x,dims.y);

    #ifdef FST_EDITOR
    b8 editor = 0;
    b8 prevKey = 0;
    #endif

    Tgame game;

    game.constr();
    game.init();

    f32 lasttime = glfwGetTime();

    while (!fst_shouldClose(state)) {
        fst_poll(state);

        time = glfwGetTime();
        f32 delta = time - lasttime;

        game.update(delta);
        game.render();

        game.scene->recupdate(delta);
        game.scene->recrender();

        #ifdef FST_EDITOR
        b8 curKey = glfwGetKey((GLFWwindow*)state, GLFW_KEY_F1);
        if (curKey == GLFW_PRESS && prevKey == GLFW_RELEASE)
            editor = !editor;
        prevKey = curKey;

        if(editor) {
            fst_render_rect(rstate, 0,0,1,1,1,1,1,1);
        }
        #endif

        fst_render_flush(rstate);

        fst_swapBuffer(state);
    }

    game.end();

    delete game.scene;

    #ifdef FST_EDITOR
    #endif

    fst_render_end(rstate);
    fst_end(state);
    return 0;
}

#define FST_MAIN(class)                                                \
int main(void) {                                                       \
    return fst_windowDoShit<class>("title", ((v2){800,600})); \
}

#endif
