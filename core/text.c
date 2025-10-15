#include "text.hh"

#include <core/render.hh>
#include <core/texture.hh>

namespace fur {
    void Text::unloadFont(Font* font) {
        texture::unload(font->atlas);
        delete font;
    }

    Font* Text::loadFont(const char* file) {
        Font* font = new Font();
        font->atlas = texture::load(file);
        font->charW = font->atlas->width/16;
        font->charH = font->atlas->height/16;
        return font;
    }

    void Text::drawFont(Font* font, mat4 transf, const char* text, f32 size, v2 pos, v4 col) {
        s32 charX = 0, charY = 0;
        for (s32 i = 0; text[i] != '\0'; ++i) {
            char cur = text[i];
            s32 sx = cur >> 4;
            s32 sy = cur & 0xF;

            render->tex(
                font->atlas,
                transf,
                v2{
                    pos.x + charX * font->charW * size,
                    pos.y + charY * font->charH * size
                },
                v2{
                    font->charW * size,
                    font->charH * size
                },
                v4{
                    (f32)sx * font->charW,
                    (f32)sy * font->charH,
                    (f32)font->charW,
                    (f32)font->charH
                },
                col
                );

            ++charX;
            if (text[i] == '\n') {
                ++charY;
                charX = 0;
            }
        }
    }
}
