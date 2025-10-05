#include <forrst.hh>
#include <core/render.hh>

class square : public FSTnode {
public:
    void render() {
        fst_render_rect(rstate, 0,0,1,1,1,0,0,1);
    }
};

class game : public FSTgame {
public:
    void init() {
        scene->addChild(new square());
    }

    void render() {
        fst_render_clear(rstate, .2,.4,.3,1);
    }
};



int main(void) {
    return fst_windowDoShit<game>("title", ((v2){800,600}));
}

