#ifndef FST_RENDER_H
#define FST_RENDER_H

#ifdef __cplusplus
extern "C" {
#endif

#include <core/macros.h>

void* fst_render_init(void);
void fst_render_resize(void* state, s32 width, s32 height);
void fst_render_end(void* state);

#ifdef __cplusplus
}
#endif

#endif
