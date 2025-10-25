#ifndef FUR_INPUT_H
#define FUR_INPUT_H

#include <core/macros.h>
#include <platf/state.h>

typedef enum {
    FUR_RELEASED,
    FUR_PRESSED,
    FUR_HELD,
    FUR_INACTIVE
} FUR_keyState;

typedef enum {
// misc
    FUR_KEY_ESCAPE,
    FUR_KEY_CAPS,
    FUR_KEY_SPACE, FUR_KEY_TAB,
    FUR_KEY_BACKSPACE, FUR_KEY_DELETE,
    FUR_KEY_HOME, FUR_KEY_END,
    FUR_KEY_PAGEUP, FUR_KEY_PAGEDOWN,
    FUR_KEY_INSERT,

// modifiers
    FUR_KEY_LSHIFT, FUR_KEY_RSHIFT,
    FUR_KEY_LCTRL,  FUR_KEY_RCTRL,
    FUR_KEY_LALT,   FUR_KEY_RALT,
    FUR_KEY_LSUPER, FUR_KEY_RSUPER, // win key

// arrow keys
             FUR_KEY_UP,
    FUR_KEY_LEFT, FUR_KEY_RIGHT,
            FUR_KEY_DOWN, 

// alphabetical
    FUR_KEY_A, FUR_KEY_B, FUR_KEY_C,
    FUR_KEY_D, FUR_KEY_E, FUR_KEY_F, 
    FUR_KEY_G, FUR_KEY_H, FUR_KEY_I,
    FUR_KEY_J, FUR_KEY_K, FUR_KEY_L,
    FUR_KEY_M, FUR_KEY_N, FUR_KEY_O,
    FUR_KEY_P, FUR_KEY_Q, FUR_KEY_R,
    FUR_KEY_S, FUR_KEY_T, FUR_KEY_U,
    FUR_KEY_V, FUR_KEY_W, FUR_KEY_X,
          FUR_KEY_Y, FUR_KEY_Z,

// numerical
    FUR_KEY_1, FUR_KEY_2, FUR_KEY_3,
    FUR_KEY_4, FUR_KEY_5, FUR_KEY_6,
    FUR_KEY_7, FUR_KEY_8, FUR_KEY_9,
               FUR_KEY_0,

// function
    FUR_KEY_F1, FUR_KEY_F2, FUR_KEY_F3,
    FUR_KEY_F4, FUR_KEY_F5, FUR_KEY_F6,
    FUR_KEY_F7, FUR_KEY_F8, FUR_KEY_F9,
    FUR_KEY_F10, FUR_KEY_F11, FUR_KEY_F12,

// todo: add symbols and other stuff

    FUR_KEY_LAST
} FUR_key;

static FUR_keyState fur_input_keys[FUR_KEY_LAST];

void fur_input_poll(FUR_platfState* platf);

static inline b8 fur_input_isKeyPressed(FUR_key key)  { return fur_input_keys[key] == FUR_PRESSED; }
static inline b8 fur_input_isKeyHeld(FUR_key key)     { return fur_input_keys[key] == FUR_PRESSED || fur_input_keys[key] == FUR_HELD; }
static inline b8 fur_input_isKeyReleased(FUR_key key) { return fur_input_keys[key] == FUR_RELEASED; }

#endif
