#ifndef FUR_RENDER_GL_MISC_H
#define FUR_RENDER_GL_MISC_H

#include <core/macros.h>
#include <core/matrix.h>

/* ====== DATATYPES ====== */

typedef struct {
    f32 x, y, w, h;
    f32 r, g, b, a;
    f32 sx,sy,sw,sh;
    mat4 transform;
} FUR_gl_instanceData;

#endif
