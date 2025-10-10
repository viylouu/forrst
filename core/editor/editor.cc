#include "editor.hh"

#include <core/render.hh>
#include <GLFW/glfw3.h>
#include <core/node.hh>
#include <core/text.hh>

namespace fur {
    Editor::Editor(Render* render, Text* text) {
        this->render = render;
        this->text = text;

        font = text->loadFont("data/eng/font.png");
    }

    Editor::~Editor() {
        text->unloadFont(font);
    }
    
    s32 Editor::hierarchy(Node* node, mat4 ident, s32 y, s32 indent) {
        if (y > -font->charH*2)
            text->drawFont(font, ident, node->name, 2, v2{2.f+indent*font->charW*4,(f32)y+2}, v4{0,0,0,1});

        for (s32 i = 0; i < (s32)node->children.size(); ++i) {
            y = hierarchy(node->children[i], ident, y + font->charH*2, indent+1);

            if (y > height)
                return y;
        }

        return y;
    }

    void Editor::main(s32 width, s32 height, Node* scene) {
        mat4 ident;
        mat4_identity(&ident);

        this->width = width;
        this->height = height;

        render->rect(ident, v2{0,0}, v2{256,(f32)height}, v4{1,1,1,1});

        hierarchy(scene, ident, 0,0);
    }
}
