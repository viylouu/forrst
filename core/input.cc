#include "input.hh"

#include <GLFW/glfw3.h>

namespace fur {
    KeyState keys[GLFW_KEY_LAST];
    KeyState mouseb[GLFW_MOUSE_BUTTON_LAST];

    void stateResolver(KeyState* now, KeyState prev) {
        if (*now == KeyState::RELEASED && ( prev == KeyState::RELEASED || prev == KeyState::UNPRESSED )) *now = KeyState::UNPRESSED;
        if (*now == KeyState::PRESSED && ( prev == KeyState::PRESSED || prev == KeyState::HELD )) *now = KeyState::HELD;
    }

    void Input::poll(GLFWwindow* window) {
        f64 mx,my;
        glfwGetCursorPos(window, &mx,&my);
        mouse.x = mx;
        mouse.y = my;

        for (s32 i = 0; i < GLFW_KEY_LAST; ++i) {
            KeyState prev = keys[i];
            keys[i] = (KeyState)glfwGetKey(window, i);
            stateResolver(&keys[i], prev);
        }

        for (s32 i = 0; i < GLFW_MOUSE_BUTTON_LAST; ++i) {
            KeyState prev = mouseb[i];
            mouseb[i] = (KeyState)glfwGetMouseButton(window, i);
            stateResolver(&mouseb[i], prev);
        }
    }

    KeyState Input::getKeyState(s32 scancode) { return keys[scancode]; }
    KeyState Input::getMouseState(s32 scancode) { return mouseb[scancode]; }

    b8 Input::isKeyHeld(s32 scancode) { return keys[scancode] == KeyState::PRESSED || keys[scancode] == KeyState::HELD; }
    b8 Input::isKeyPressed(s32 scancode) { return keys[scancode] == KeyState::PRESSED; }
    b8 Input::isKeyReleased(s32 scancode) { return keys[scancode] == KeyState::RELEASED; }

    b8 Input::isMouseHeld(s32 scancode) { return mouseb[scancode] == KeyState::PRESSED || mouseb[scancode] == KeyState::HELD; }
    b8 Input::isMousePressed(s32 scancode) { return mouseb[scancode] == KeyState::PRESSED; }
    b8 Input::isMouseReleased(s32 scancode) { return mouseb[scancode] == KeyState::RELEASED; }
}
