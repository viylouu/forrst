#ifndef FUR_EDITOR_HH
#define FUR_EDITOR_HH

#include <core/node.hh>
#include <core/render.hh>
#include <core/text.hh>

namespace fur {
    class Editor {
    private:
        Render* render;
        Text* text;
        Input* input;

        Font* font;

        s32 width, height;
    public:
        Editor(Render* render, Text* text, Input* input);
        ~Editor();
        s32 hierarchy(Node* node, mat4 ident, s32 y, s32 indent);
        void main(s32 width, s32 height, Node* scene);
    };
}

#endif
