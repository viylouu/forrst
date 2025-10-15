#ifndef FUR_INPUT_H
#define FUR_INPUT_H

#include <core/macros.h>
#include <GLFW/glfw3.h>

typedef enum {
    FUR_RELEASED,
    FUR_PRESSED,
    FUR_HELD,
    FUR_UNPRESSED
} FUR_keyState;

typedef struct {
    v2 mouse;
} FUR_inputState;

void fur_pollInput(GLFWwindow* window);

FUR_keyState fur_getKeyState(s32 scancode);
FUR_keyState fur_getMouseState(s32 scancode);

b8 fur_isKeyHeld(s32 scancode);
b8 fur_isKeyPressed(s32 scancode);
b8 fur_isKeyReleased(s32 scancode);

b8 fur_isMouseHeld(s32 scancode);
b8 fur_isMousePressed(s32 scancode);
b8 fur_isMouseReleased(s32 scancode);

#endif
