#ifndef FUR_INPUT_HH
#define FUR_INPUT_HH

#include <core/macros.h>
#include <GLFW/glfw3.h>

namespace fur {
    enum class KeyState {
        RELEASED,
        PRESSED,
        HELD,
        UNPRESSED
    };

    class Input {
    public:
        v2 mouse;

        void poll(GLFWwindow* window);

        KeyState getKeyState(s32 scancode);
        KeyState getMouseState(s32 scancode);

        b8 isKeyHeld(s32 scancode);
        b8 isKeyPressed(s32 scancode);
        b8 isKeyReleased(s32 scancode);

        b8 isMouseHeld(s32 scancode);
        b8 isMousePressed(s32 scancode);
        b8 isMouseReleased(s32 scancode);
    };
}

#endif
