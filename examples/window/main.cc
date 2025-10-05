#include <forrst.hh>
#include <core/render.hh>
#include <cstdlib>

class FSTrenderer : public FSTcomponent {
public:
    char* t_name;

    void init() {
        FSTvarInfo info = { &t_name, "test name", FST_TYPEOF_STRING };
        publics.push_back(info); 
    }

    void render() {
        fst_render_rect(rstate, 
            (rand()%16384)/8192.f-1,(rand()%16384)/8192.f-1,(rand()%16384)/16384.f,(rand()%16384)/16384.f,(rand()%16384)/16384.f,(rand()%16384)/16384.f,(rand()%16384)/16384.f,(rand()%16384)/16384.f);
    }
};

class game : public FSTgame {
public:
    s32 tick;

    void init() {
        for (s32 i = 0; i < 16384; ++i) {
            FSTnode* node = new FSTnode();
            node->addComponent(new FSTrenderer());
            scene->addChild(node);
        }
        tick = 0;
    }

    void render() {
        srand(++tick);
        fst_render_clear(rstate, .2,.4,.3,1);       
    }
};

FST_MAIN(game);
