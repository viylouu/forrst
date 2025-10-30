#include "draw.h"

#include <core/macros.h>
#include <stdio.h>
#include <string.h>
#include <render/gl/loader.h>
#include <render/gl/main.h>
#include <render/gl/structs.h>
#include <core/render/gl/renderTarget.h>

/* ====== FUNCS ====== */

void fur_render_gl_clear(FUR_gl_renderState* render, FUR_renderTarget* target, f32 r, f32 g, f32 b) {
    fur_render_gl_flush(render);

    easy_set_target(&render->proj, target, render->width, render->height);

    glClearColor(r,g,b, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void fur_render_gl_flush(FUR_gl_renderState* render) {
    if (render->batch_amt == 0) return;

    switch(render->batch_type) {
        case FUR_GL_BATCH_RECT:
            fur_render_gl_2d_rect_draw(&render->rect2d, &render->proj, render->shitty_vao, &render->batch, render->batch_amt, render->batch_target, render->width, render->height); break;
        case FUR_GL_BATCH_TEX:
            fur_render_gl_2d_tex_draw(&render->tex2d, &render->proj, render->shitty_vao, &render->batch, render->batch_amt, CAST(FUR_texture*, render->batch_other)->spec, render->batch_target, render->width, render->height); break;
        case FUR_GL_BATCH_RENDER_TARGET:
            fur_render_gl_2d_renderTarget_draw(&render->targ2d, &render->proj, render->shitty_vao, &render->batch, render->batch_amt, render->batch_other, render->batch_target, render->width, render->height); break;
        default:
            WARN("type (%d) has no draw function!\n", render->batch_type);
    }

    render->batch_amt = 0;
}

/* ====== FUNCS ====== */

void fur_render_gl_rect(FUR_gl_renderState* render, FUR_renderTarget* target, mat4 transf, v2 pos, v2 size, v4 col) {
    if (render->batch_amt >= 8192) fur_render_gl_flush(render);
    if (render->batch_type != FUR_GL_BATCH_RECT) fur_render_gl_flush(render);
    if (render->batch_target != target) fur_render_gl_flush(render);

    render->batch_type = FUR_GL_BATCH_RECT;
    render->batch_target = target;

    FUR_gl_instanceData data = {0};

    data.x = pos.x; data.y = pos.y;
    data.w = size.x; data.h = size.y;
    data.r = col.x; data.g = col.y;
    data.b = col.z; data.a = col.w;
    
    memcpy(&data.transform, transf, sizeof(mat4));

    render->batch[render->batch_amt] = data;
    ++render->batch_amt;
}

void fur_render_gl_tex(FUR_gl_renderState* render, FUR_renderTarget* target, FUR_texture* texture, mat4 transf, v2 pos, v2 size, v4 sample, v4 col) {
    if (render->batch_amt >= 8192) fur_render_gl_flush(render);
    if (render->batch_type != FUR_GL_BATCH_TEX) fur_render_gl_flush(render);
    if (render->batch_other != texture) fur_render_gl_flush(render);
    if (render->batch_target != target) fur_render_gl_flush(render);

    render->batch_type = FUR_GL_BATCH_TEX;
    render->batch_other = texture;

    FUR_gl_instanceData data = {0};

    data.x = pos.x; data.y = pos.y;
    data.w = size.x; data.h = size.y;
    data.r = col.x; data.g = col.y;
    data.b = col.z; data.a = col.w;
    data.sx = sample.x; data.sy = sample.y;
    data.sw = sample.z; data.sh = sample.w;

    memcpy(&data.transform, transf, sizeof(mat4));

    render->batch[render->batch_amt] = data;
    ++render->batch_amt;
}

void fur_render_gl_renderTarget(FUR_gl_renderState* render, FUR_renderTarget* out_target, FUR_renderTarget* in_target, mat4 transf, v2 pos, v2 size, v4 sample, v4 col) {
    if (render->batch_amt >= 8192) fur_render_gl_flush(render);
    if (render->batch_type != FUR_GL_BATCH_RENDER_TARGET) fur_render_gl_flush(render);
    if (render->batch_other != in_target) fur_render_gl_flush(render);
    if (render->batch_target != out_target) fur_render_gl_flush(render);

    render->batch_type = FUR_GL_BATCH_RENDER_TARGET;
    render->batch_other = in_target;

    FUR_gl_instanceData data = {0};

    data.x = pos.x; data.y = pos.y;
    data.w = size.x; data.h = size.y;
    data.r = col.x; data.g = col.y;
    data.b = col.z; data.a = col.w;
    data.sx = sample.x; data.sy = sample.y;
    data.sw = sample.z; data.sh = sample.w;

    memcpy(&data.transform, transf, sizeof(mat4));

    render->batch[render->batch_amt] = data;
    ++render->batch_amt;
}
