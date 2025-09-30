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
    // empty (for now, muahahah)
} FSTwindowDoShitOPS;
#define fst_windowDoShit(title, width, height, ...) \
    EXPLICIT_fst_windowDoShit((title), (width), (height), (FSTwindowDoShitOPS){ __VA_ARGS__ })
int EXPLICIT_fst_windowDoShit(const char* title, s32 width, s32 height, FSTwindowDoShitOPS ops);

/*
 * Main Loop OPS
 */


#endif
