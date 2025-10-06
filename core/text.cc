#include "text.hh"

#include <core/render.hh>
#include <core/texture.h>

FURfont* fur_text_loadFont(const char* file) {
    FURfont* font = new FURfont();
    font->atlas = fur_texture_load(file);
    font->charW = font->atlas->width/16;
    font->charH = font->atlas->height/16;
    return font;
}

void fur_text_unloadFont(FURfont* font) {
    fur_texture_unload(font->atlas);
    free(font);
}

void fur_text_draw(void* data, FURrenderTarget* targ, FURfont* font, mat4 transf, const char* text, f32 size, f32 x, f32 y, f32 r, f32 g, f32 b, f32 a) {
    s32 charX = 0, charY = 0;
    for (s32 i = 0; text[i] != '\0'; ++i) {
        char cur = text[i];
        s32 sx = cur >> 4;
        s32 sy = cur & 0xF;

        fur_render_tex(
            data,
            targ,
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
