#include <forrst.h>

#include <GL/gl.h>

void render(void) {
    glClearColor(.2,.4,.3,1);
    glClear(GL_COLOR_BUFFER_BIT);
}

int main(void) {
    FSTwindowDoShitOPS ops = {};
    ops.render = render;
    v2 dims = {800,600};
    return fst_windowDoShit("title", dims, ops);
}
