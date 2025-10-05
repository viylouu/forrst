#include <forrst.hh>
#include <core/render.hh>
#include <cstdlib>

class square : public FSTnode {
public:
    void render() {
        fst_render_rect(rstate, 
            (rand()%16384)/8192.f-1,(rand()%16384)/8192.f-1,(rand()%16384)/16384.f,(rand()%16384)/16384.f,(rand()%16384)/16384.f,(rand()%16384)/16384.f,(rand()%16384)/16384.f,(rand()%16384)/16384.f);
    }
};

class game : public FSTgame {
public:
    s32 tick;

    void init() {
        for (s32 i = 0; i < 16384; ++i)
            scene->addChild(new square());
        tick = 0;
    }

    void render() {
srand(++tick);
        fst_render_clear(rstate, .2,.4,.3,1);
    }
};

FST_MAIN(game);
