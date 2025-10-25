#include "input.h"

#include <platf/glfw/main.h>
#include <core/input.h>

void fur_input_glfw_updateAt(FUR_glfw_platfState* platf, s32 glfwPos, s32 i_asFur) {
    FUR_keyState prev = fur_input_keys[i_asFur];
    FUR_keyState cur = fur_input_keys[i_asFur] = glfwGetKey(platf->window, glfwPos);
    if (cur == FUR_RELEASED && ( prev == FUR_RELEASED || prev == FUR_INACTIVE )) fur_input_keys[i_asFur] = FUR_INACTIVE;
    if (cur == FUR_PRESSED && ( prev == FUR_PRESSED || prev == FUR_HELD )) fur_input_keys[i_asFur] = FUR_HELD;
}

#define ua(a,b) fur_input_glfw_updateAt(platf, a,b)

void fur_input_glfw_poll(FUR_glfw_platfState* platf) {
    s32 off;

// alphabetical
    off = FUR_KEY_A - GLFW_KEY_A;
    for(s32 i = GLFW_KEY_A; i <= GLFW_KEY_Z; ++i)
        ua(i, i+off);

// numerical
    ua(GLFW_KEY_0, FUR_KEY_0);
    off = FUR_KEY_1 - GLFW_KEY_1;
    for(s32 i = GLFW_KEY_1; i <= GLFW_KEY_9; ++i)
        ua(i, i+off);

// function
    off = FUR_KEY_F1 - GLFW_KEY_F1;
    for(s32 i = GLFW_KEY_F1; i <= GLFW_KEY_F12; ++i)
        ua(i, i+off);

// arrow keys
    ua(GLFW_KEY_UP, FUR_KEY_UP);
    ua(GLFW_KEY_DOWN, FUR_KEY_DOWN);
    ua(GLFW_KEY_LEFT, FUR_KEY_LEFT);
    ua(GLFW_KEY_RIGHT, FUR_KEY_RIGHT);

// misc
    ua(GLFW_KEY_ESCAPE, FUR_KEY_ESCAPE);
    ua(GLFW_KEY_CAPS_LOCK, FUR_KEY_CAPS);
    ua(GLFW_KEY_SPACE, FUR_KEY_SPACE);
    ua(GLFW_KEY_TAB, FUR_KEY_TAB);
    ua(GLFW_KEY_BACKSPACE, FUR_KEY_BACKSPACE);
    ua(GLFW_KEY_DELETE, FUR_KEY_DELETE);
    ua(GLFW_KEY_HOME, FUR_KEY_HOME);
    ua(GLFW_KEY_END, FUR_KEY_END);
    ua(GLFW_KEY_PAGE_UP, FUR_KEY_PAGEUP);
    ua(GLFW_KEY_PAGE_DOWN, FUR_KEY_PAGEDOWN);
    ua(GLFW_KEY_INSERT, FUR_KEY_INSERT);
}
