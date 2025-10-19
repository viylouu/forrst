#include "draw.h"

#include <render/gl/loader.h>
#include <render/gl/main.h>

/* ====== FUNCS ====== */

void fur_render_gl_clear(FUR_gl_renderState* render, f32 r, f32 g, f32 b) {
    (void)render;

    glClearColor(r,g,b, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}
