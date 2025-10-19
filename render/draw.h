#ifndef FUR_RENDER_DRAW_H
#define FUR_RENDER_DRAW_H

#include <render/state.h>
#include <core/macros.h>

/* ====== FUNCS ====== */

void fur_render_clear(FUR_renderState* render, f32 r, f32 g, f32 b);

void fur_render_flush(FUR_renderState* render);

#endif
