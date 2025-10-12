#include "editor.hh"

#include <core/render.hh>
#include <GLFW/glfw3.h>
#include <core/node.hh>
#include <core/text.hh>
#include <core/input.hh>

namespace fur {
    Editor::Editor(Render* render, Text* text, Input* input) {
        this->render = render;
        this->text = text;
        this->input = input;

        font = text->loadFont("data/eng/font.png");
    }

    Editor::~Editor() {
        text->unloadFont(font);
    }
    
    s32 Editor::hierarchy(Node* node, mat4 ident, s32 y, s32 indent) {
        if (y > -font->charH*2) {
            v4 rect = v4{
                0, (f32)y,
                256, font->charH*2.f
                };

            if (input->mouse.x > rect.x && input->mouse.x < rect.x+rect.z &&
                input->mouse.y > rect.y && input->mouse.y < rect.y+rect.w) {
                render->rect(NULL, v2{rect.x,rect.y}, v2{rect.z,rect.w}, v4{.9f,.9f,.9f,1});

                if (input->isMousePressed(GLFW_MOUSE_BUTTON_LEFT))
                    node->editor_open = !node->editor_open;
            }

            text->drawFont(font, ident, node->editor_open? "v" : ">", 2, v2{8.f,(f32)y+2}, v4{0,0,0,1});
            text->drawFont(font, ident, node->name, 2, v2{2.f+indent*font->charW*4+font->charW*4,(f32)y+2}, v4{0,0,0,1});
        }

        if (node->editor_open)
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
