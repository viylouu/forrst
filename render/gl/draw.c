#include "draw.h"

#include <core/macros.h>
#include <stdio.h>
#include <string.h>
#include <render/gl/loader.h>
#include <render/gl/main.h>
#include <render/gl/structs.h>

/* ====== FUNCS ====== */

void fur_render_gl_clear(FUR_gl_renderState* render, f32 r, f32 g, f32 b) {
    (void)render;

    glClearColor(r,g,b, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void fur_render_gl_flush(FUR_gl_renderState* render) {
    if (render->batch_amt == 0) return;

    switch(render->batch_type) {
        case FUR_GL_BATCH_RECT:
            fur_render_gl_2d_rect_draw(&render->rect2d, render->proj, render->shitty_vao, &render->batch, render->batch_amt); break;
        default:
            WARN("type (%d) has no draw function!\n", render->batch_type);
    }

    render->batch_amt = 0;
}

/* ====== FUNCS ====== */

void fur_render_gl_rect(FUR_gl_renderState* render, mat4 transf, v2 pos, v2 size, v4 col) {
    if (render->batch_amt >= 65536) fur_render_gl_flush(render);
    if (render->batch_type != FUR_GL_BATCH_RECT) fur_render_gl_flush(render);

    render->batch_type = FUR_GL_BATCH_RECT;

    FUR_gl_instanceData data = {0};

    data.x = pos.x; data.y = pos.y;
    data.w = size.x; data.h = size.y;
    data.r = col.x; data.g = col.y;
    data.b = col.z; data.a = col.w;
    
    memcpy(&data.transform, transf, sizeof(mat4));

    render->batch[render->batch_amt] = data;

    ++render->batch_amt;
}
