#ifndef FRST_FORRST_HH
#define FRST_FORRST_HH

#include <core/macros.h>
#include <core/render.hh>
#include <core/auto/load_gl.h>
#include <core/node.hh>
#include <GLFW/glfw3.h>
#include <core/editor/editor.hh>

#define FST_WIDTH fst_query_width()
#define FST_HEIGHT fst_query_height()

static void* rstate;

void fst_cb_size(GLFWwindow* window, s32 width, s32 height);
void* fst_init(const char* title, s32 width, s32 height);
char fst_shouldClose(void* state);
void fst_poll(void* state);
void fst_swapBuffer(void* state);
void fst_end(void* state);
static inline s32 fst_query_width() { return ((FSTrenderState*)rstate)->width; }
static inline s32 fst_query_height() { return ((FSTrenderState*)rstate)->height; }

static f64 time;

class FSTgame {
public:
    FSTnode* scene;

    void constr()   { 
        scene = new FSTnode(); 
        scene->name = "scene";
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

    glfwSetWindowUserPointer((GLFWwindow*)state, rstate);
    glfwSetFramebufferSizeCallback((GLFWwindow*)state, fst_cb_size);

    glViewport(0,0,dims.x,dims.y);

#ifdef _WIN32
    glfwSetWindowSize((GLFWwindow*)state, dims.x+1,dims.y+1);
    glfwSetWindowSize((GLFWwindow*)state, dims.x,dims.y);
#endif

    #ifdef FST_EDITOR
    b8 editor = 1;
    b8 prevKey = 0;
    void* estate = fst_editor_init();
    #endif

    Tgame game;

    game.constr();
    game.init();

    f32 lasttime = glfwGetTime();

    while (!fst_shouldClose(state)) {
        fst_poll(state);

        time = glfwGetTime();
        f32 delta = time - lasttime;
        lasttime = glfwGetTime();

        game.update(delta);
        game.render();

        game.scene->recupdate(delta);
        game.scene->recrender();

        #ifdef FST_EDITOR
        b8 curKey = glfwGetKey((GLFWwindow*)state, GLFW_KEY_F1);
        if (curKey == GLFW_PRESS && prevKey == GLFW_RELEASE)
            editor = !editor;
        prevKey = curKey;

        if(editor)
            fst_editor(estate, state, rstate, game.scene);
        #endif

        fst_render_flush(rstate);

        fst_swapBuffer(state);
    }

    game.end();

    delete game.scene;

    #ifdef FST_EDITOR
    fst_editor_end(estate);
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
