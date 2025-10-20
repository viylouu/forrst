#ifndef FUR_MATRIX_H
#define FUR_MATRIX_H

#include <core/macros.h>

typedef f32 mat4[16];

#define mat4_identity { 1,0,0,0, 0,1,0,0, 0,0,1,0, 0,0,0,1 }

void mat4_make(
    mat4* mat,
    f32 m00, f32 m01, f32 m02, f32 m03,
    f32 m10, f32 m11, f32 m12, f32 m13,
    f32 m20, f32 m21, f32 m22, f32 m23,
    f32 m30, f32 m31, f32 m32, f32 m33
);

void mat4_multiply(mat4* out, const mat4 a, const mat4 b);

void mat4_ortho(
    mat4* mat, 
    f32 left, f32 right,
    f32 bottom, f32 top,
    f32 near, f32 far
);

void mat4_set_identity(mat4* mat);

void mat4_translate(mat4* mat, f32 x, f32 y, f32 z);
void mat4_scale(mat4* mat, f32 x, f32 y, f32 z);

void mat4_rotateX(mat4* mat, f32 ang);
void mat4_rotateY(mat4* mat, f32 ang);
void mat4_rotateZ(mat4* mat, f32 ang);

#endif
