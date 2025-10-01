#include <forrst.h>

#include <GL/gl.h>

void render(void) {
    glClearColor(.2,.4,.3,1);
    glClear(GL_COLOR_BUFFER_BIT);
}

int main(void) {
    return fst_windowDoShit("title", ((v2){800.f,600.f}), .render = render);
}
