#include <forrst.hh>
#include <core/render.hh>

#include <GL/gl.h>
#include <core/load_gl.h>
#include <stdlib.h>
#include <algorithm>

class square : public FSTnode {
public:
    void render() {
        fst_render_rect(rstate, 0,0,1,1,1,0,0,1);
    }
};

class game : public FSTgame {
public:
    square* sqr;

    void init() {
        sqr = new square();

        scene->addChild(sqr);
    }

    void render() {
        glClearColor(.2,.4,.3,1);
        glClear(GL_COLOR_BUFFER_BIT);
    }
};



int main(void) {
    return fst_windowDoShit<game>("title", ((v2){800,600}));
}

