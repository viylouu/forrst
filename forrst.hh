#ifndef FRST_FORRST_H
#define FRST_FORRST_H

#include <core/macros.h>
#include <core/render.h>
#include <core/load_gl.h>

void* fst_init(const char* title, s32 width, s32 height);
char fst_shouldClose(void* state);
void fst_poll(void* state);
void fst_swapBuffer(void* state);
void fst_end(void* state);

class FSTgame {
public:
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
    void* rstate = fst_render_init();

    Tgame game;

    game.init();

    while (!fst_shouldClose(state)) {
        fst_poll(state);

        game.update();
        game.render();

        fst_swapBuffer(state);
    }

    game.end();

    fst_render_end(rstate);
    fst_end(state);
    return 0;
}

#endif
