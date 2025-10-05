#ifndef FRST_FORRST_HH
#define FRST_FORRST_HH

#include <core/macros.h>
#include <core/render.hh>
#include <core/load_gl.h>
#include <core/node.hh>

void* fst_init(const char* title, s32 width, s32 height);
char fst_shouldClose(void* state);
void fst_poll(void* state);
void fst_swapBuffer(void* state);
void fst_end(void* state);

static void* rstate;

class FSTgame {
public:
    FSTnode* scene;

    void constr()   { 
        scene = new FSTnode(); 
    }

    virtual void init()   {}
    virtual void update() {}
    virtual void render() {}
    virtual void end()    {}
};

template<typename Tgame>
s32 fst_windowDoShit(const char* title, v2 dims) {
    FSTgame* forcetype = static_cast<Tgame*>(0); (void)forcetype;

    void* state = fst_init(title, dims.x,dims.y);
    fst_gl_load();
    rstate = fst_render_init();

    Tgame game;

    game.constr();
    game.init();

    while (!fst_shouldClose(state)) {
        fst_poll(state);

        game.update();
        game.render();

        game.scene->recupdate();
        game.scene->recrender();

        fst_render_flush(rstate);

        fst_swapBuffer(state);
    }

    game.end();

    delete game.scene;

    fst_render_end(rstate);
    fst_end(state);
    return 0;
}

#define FST_MAIN(class)                                                \
int main(void) {                                                       \
    return fst_windowDoShit<class>("title", ((v2){800,600})); \
}

#endif
