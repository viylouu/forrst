#ifndef FUR_FURRY_HH
#define FUR_FURRY_HH

#include <core/macros.h>
#include <core/render.hh>
#include <core/auto/load_gl.h>
#include <core/node.hh>
#include <GLFW/glfw3.h>
#include <core/editor/editor.hh>

#define FUR_WIDTH fur_query_width()
#define FUR_HEIGHT fur_query_height()

static void* rstate;

void fur_cb_size(GLFWwindow* window, s32 width, s32 height);
void* fur_init(const char* title, s32 width, s32 height);
char fur_shouldClose(void* state);
void fur_poll(void* state);
void fur_swapBuffer(void* state);
void fur_end(void* state);
static inline s32 fur_query_width() { return ((FURrenderState*)rstate)->width; }
static inline s32 fur_query_height() { return ((FURrenderState*)rstate)->height; }

static f64 time;

class FURgame {
public:
    FURnode* scene;

    virtual void init()            {}
    virtual void update(f32 delta) {}
    virtual void render()          {}
    virtual void end()             {}
};

template<typename Tgame>
s32 fur_windowDoShit(const char* title, v2 dims) {
    FURgame* forcetype = static_cast<Tgame*>(0); (void)forcetype;

    void* state = fur_init(title, dims.x,dims.y);
    fur_gl_load();
    rstate = fur_render_init();

    glfwSetWindowUserPointer((GLFWwindow*)state, rstate);
    glfwSetFramebufferSizeCallback((GLFWwindow*)state, fur_cb_size);

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

    Tgame game;

    game.scene = new FURnode();
    game.scene->name = "scene";

    game.init();

    f32 lasttime = glfwGetTime();

    while (!fur_shouldClose(state)) {
        fur_poll(state);

        time = glfwGetTime();
        f32 delta = time - lasttime;
        lasttime = glfwGetTime();

        game.update(delta);
        game.scene->recupdate(delta);

        game.render();
        game.scene->recrender();

        #ifdef FUR_EDITOR
        b8 curKey = glfwGetKey((GLFWwindow*)state, GLFW_KEY_F1);
        if (curKey == GLFW_PRESS && prevKey == GLFW_RELEASE)
            editor = !editor;
        prevKey = curKey;

        if(editor)
            fur_editor(estate, state, rstate, game.scene);
        #endif

        fur_render_flush(rstate);

        fur_swapBuffer(state);
    }

    game.end();

    delete game.scene;

    #ifdef FST_EDITOR
    fur_editor_end(estate);
    #endif

    fur_render_end(rstate);
    fur_end(state);
    return 0;
}

#define FUR_MAIN(class)                                                \
int main(void) {                                                       \
    return fur_windowDoShit<class>("title", ((v2){800,600})); \
}

#endif
