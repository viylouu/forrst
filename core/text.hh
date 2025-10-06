#ifndef FST_TEXT_HH
#define FST_TEXT_HH

#include <core/texture.h>
#include <core/mat4.h>

typedef struct {
    int charW, charH;
    FSTtexture* atlas;
} FSTfont;

FSTfont* fst_text_loadFont(const char* file);
void fst_text_unloadFont(FSTfont* font);
void fst_text_draw(void* data, FSTfont* font, mat4 transf, const char* text, f32 size, f32 x, f32 y, f32 r, f32 g, f32 b, f32 a) ;

#endif
