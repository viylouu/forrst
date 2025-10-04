#include <forrst.hh>
#include <core/macros.h>

#include <GL/gl.h>

class game : public FSTgame {
public:
    void render(void) {
        glClearColor(.2,.4,.3,1);
        glClear(GL_COLOR_BUFFER_BIT);
    }
};

int main(void) {
    return fst_windowDoShit<game>("title", ((v2){800,600}));
}
