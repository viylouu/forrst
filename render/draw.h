#ifndef FUR_RENDER_DRAW_H
#define FUR_RENDER_DRAW_H

#include <render/state.h>
#include <core/macros.h>
#include <core/matrix.h>

/* ====== FUNCS ====== */

void fur_render_clear(FUR_renderState* render, f32 r, f32 g, f32 b);

void fur_render_flush(FUR_renderState* render);

/* ====== STRUCTS ====== */

typedef struct {
    v2 pos;
    v2 size;
    v4 col;
    mat4 transf;
} OP_fur_render_rect;

/* ====== FUNCS ====== */

void IMPL_fur_render_rect(FUR_renderState* render, OP_fur_render_rect op);

/* ====== MACROS ====== */

#define fur_render_rect(render, ...) \
    IMPL_fur_render_rect((render), (OP_fur_render_rect){ .pos = (v2){0,0}, .size = (v2){0,0}, .col = (v4){0,0,0,1}, .transf = mat4_identity, __VA_ARGS__ })

#endif
