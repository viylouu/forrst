#ifndef FUR_RENDER_DRAW_H
#define FUR_RENDER_DRAW_H

#include <render/state.h>
#include <core/macros.h>
#include <core/matrix.h>
#include <core/data/texture.h>
#include <stdlib.h>
#include <math.h>

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

typedef struct {
    FUR_texture* texture;
    v2 pos;
    v2 size;
    v4 sample;
    v4 col;
    mat4 transf;
} OP_fur_render_tex;

/* ====== FUNCS ====== */

void IMPL_fur_render_rect(FUR_renderState* render, OP_fur_render_rect op);
void IMPL_fur_render_tex(FUR_renderState* render, OP_fur_render_tex op);

/* ====== MACROS ====== */

#define fur_render_rect(render, ...) \
    IMPL_fur_render_rect((render), (OP_fur_render_rect){ .pos = (v2){0,0}, .size = (v2){0,0}, .col = (v4){0,0,0,1}, .transf = mat4_identity, __VA_ARGS__ })

#define fur_render_tex(render, ...) \
    IMPL_fur_render_tex((render), (OP_fur_render_tex){ .texture = NULL, .pos = (v2){0,0}, .size = (v2){NAN,NAN}, .col = (v4){0,0,0,1}, .transf = mat4_identity, .sample = (v4){NAN,NAN,NAN,NAN}, __VA_ARGS__ })

#endif
