#include <forrst.hh>
#include <core/render.hh>
#include <GL/gl.h>

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
        glClearColor(.2,.4,.3,1);
        glClear(GL_COLOR_BUFFER_BIT);
    }
};



int main(void) {
    return fst_windowDoShit<game>("title", ((v2){800,600}));
}

