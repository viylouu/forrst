#ifndef FUR_TEXT_HH
#define FUR_TEXT_HH

#include <core/texture.h>
#include <core/mat4.h>
#include <core/render.hh>

typedef struct {
    int charW, charH;
    FURtexture* atlas;
} FURfont;

FURfont* fur_text_loadFont(const char* file);
void fur_text_unloadFont(FURfont* font);
void fur_text_draw(void* data, FURrenderTarget* targ, FURfont* font, mat4 transf, const char* text, f32 size, f32 x, f32 y, f32 r, f32 g, f32 b, f32 a) ;

#endif
