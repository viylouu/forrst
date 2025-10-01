#ifndef FRST_FORRST_H
#define FRST_FORRST_H

#include <core/macros.h>

/*
 * Initialize the platform
 * Returns the state
 * Parameters:
 **** Window title
 **** Window width
 **** Window height
 */
void* fst_init(const char* title, s32 width, s32 height);

/*
 * Check if the window should close
 * Returns 0 if it shouldnt, 1 else
 */
char fst_shouldClose(void* state);

/*
 * Polls the input from the input service
 */
void fst_poll(void* state);

/*
 * Swaps the framebuffer
 */
void fst_swapBuffer(void* state);

/*
 * Cleans everything* up
 */
void fst_end(void* state);

/*
 * Main loop to handle shit for the user
 * Parameters:
 **** Window title 
 **** Window width
 **** Window height
 **** OPS
 */
typedef struct {
    void (*init)(void);
    void (*update)(void);
    void (*render)(void);
    void (*end)(void);
} FSTwindowDoShitOPS;
#define fst_windowDoShit(title, dims, ...) \
    EXPLICIT_fst_windowDoShit((title), (dims), (FSTwindowDoShitOPS){ __VA_ARGS__ })
s32 EXPLICIT_fst_windowDoShit(const char* title, v2 dims, FSTwindowDoShitOPS ops);

/*
 * Main Loop OPS
 */


#endif
