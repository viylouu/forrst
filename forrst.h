#ifndef FRST_FORRST_H
#define FRST_FORRST_H

void* fst_init(void);
char fst_shouldClose(void* state);
void fst_poll(void* state);
void fst_swapBuffer(void* state);
void fst_end(void* state);

#endif
