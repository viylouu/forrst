#include <forrst.hh>
#include <core/render.h>

#include <GL/gl.h>
#include <core/load_gl.h>
#include <stdlib.h>
#include <algorithm>

class square : public FSTnode {
public:
    FSTrenderState* state;
    float transf[16];

    void init() {
        float tmp[16] = {
            1,0,0,0,
            0,1,0,0,
            0,0,1,0,
            0,0,0,1
        };
        std::copy(tmp,tmp+16,transf);
    }

    void update() { state = (FSTrenderState*)rstate; }

    void render() {
        glUseProgram(state->rect.shader->shader);
        glBindVertexArray(state->vao);

        glUniformMatrix4fv(state->rect.loc.proj, 1,0, transf);

        glBindBuffer(GL_TEXTURE_BUFFER, state->rect.bo);
        glBufferSubData(GL_TEXTURE_BUFFER, 0, sizeof());
        
    }
};

class game : public FSTgame {
public:
    square sqr;

    void init() {
        scene->addChild(&sqr);
    }

    void render() {
        glClearColor(.2,.4,.3,1);
        glClear(GL_COLOR_BUFFER_BIT);
    }
};



int main(void) {
    return fst_windowDoShit<game>("title", ((v2){800,600}));
}

