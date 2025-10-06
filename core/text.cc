#include "text.hh"

#include <core/render.hh>
#include <core/texture.h>

FSTfont* fst_text_loadFont(const char* file) {
    FSTfont* font = new FSTfont();
    font->atlas = fst_texture_load(file);
    font->charW = font->atlas->width/16;
    font->charH = font->atlas->height/16;
    return font;
}

void fst_text_unloadFont(FSTfont* font) {
    fst_texture_unload(font->atlas);
    free(font);
}

void fst_text_draw(void* data, FSTfont* font, mat4 transf, const char* text, f32 size, f32 x, f32 y, f32 r, f32 g, f32 b, f32 a) {
    s32 charX = 0, charY = 0;
    for (s32 i = 0; text[i] != '\0'; ++i) {
        char cur = text[i];
        s32 sx = cur >> 4;
        s32 sy = cur & 0xF;

        fst_render_tex(
            data,
            font->atlas,
            transf,
            x + charX * font->charW * size,
            y + charY * font->charH * size,
            font->charW * size,
            font->charH * size,
            sx * font->charW,
            sy * font->charH,
            font->charW,
            font->charH,
            r,g,b,a
            );

        ++charX;
        if (text[i] == '\n') {
            ++charY;
            charX = 0;
        }
    }
}
