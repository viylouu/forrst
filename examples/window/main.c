#include <forrst.h>

void render(void) {
    
}

int main(void) {
    return fst_windowDoShit("title", ((v2){800.f,600.f}), .render = render);
}
