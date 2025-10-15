#ifndef FUR_TEXT_HH
#define FUR_TEXT_HH

#include <core/texture.hh>
#include <core/mat4.h>
#include <core/render.hh>

namespace fur {
    struct Font {
        int charW, charH;
        Texture* atlas;
    };

    class Text {
    public:
        fur::Render* render;
        Text(fur::Render* render) { this->render = render; }

        Font* loadFont(const char* file);
        void  unloadFont(Font* font);
        void  drawFont(Font* font, mat4 transf, const char* text, f32 size, v2 pos, v4 col);
    };
}

#endif
