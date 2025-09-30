#include <forrst.h>

int main(void) {
    void* state = fst_init();

    while (!fst_shouldClose(state)) {
        fst_poll(state);
        fst_swapBuffer(state);
    }

    fst_end(state);
    return 0;
}
