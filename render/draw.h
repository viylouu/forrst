#ifndef FUR_RENDER_DRAW_H
#define FUR_RENDER_DRAW_H

#include <render/state.h>
#include <core/macros.h>
#include <core/matrix.h>
#include <core/data/texture.h>
#include <core/renderTarget.h>
#include <stdlib.h>
#include <math.h>

/* ====== DATATYPES ====== */

typedef struct {
    FUR_renderTarget* target;
    v3 col;
} OP_fur_render_clear;

/* ====== FUNCS ====== */

void IMPL_fur_render_clear(FUR_renderState* render, OP_fur_render_clear op);

void fur_render_flush(FUR_renderState* render);

/* ====== MACROS ====== */

#define fur_render_clear(render, ...) \
    IMPL_fur_render_clear((render), (OP_fur_render_clear){ .target = NULL, .col = (v3){0,0,0}, __VA_ARGS__ })

/* ====== STRUCTS ====== */

typedef struct {
    FUR_renderTarget* target;
    v2 pos;
    v2 size;
    v4 col;
    mat4 transf;
} OP_fur_render_rect;

typedef struct {
    FUR_renderTarget* target;
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
    IMPL_fur_render_rect((render), (OP_fur_render_rect){ .target = NULL, .pos = (v2){0,0}, .size = (v2){0,0}, .col = (v4){0,0,0,1}, .transf = mat4_identity, __VA_ARGS__ })

#define fur_render_tex(render, ...) \
    IMPL_fur_render_tex((render), (OP_fur_render_tex){ .target = NULL, .texture = NULL, .pos = (v2){0,0}, .size = (v2){NAN,NAN}, .col = (v4){0,0,0,1}, .transf = mat4_identity, .sample = (v4){NAN,NAN,NAN,NAN}, __VA_ARGS__ })

#endif
