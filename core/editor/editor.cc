#include "editor.hh"

#include <core/render.hh>
#include <GLFW/glfw3.h>
#include <core/node.hh>
#include <core/text.hh>
#include <core/input.hh>
#include <imgui/imgui.h>
#include <imgui/imgui_internal.h>

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
    
    void Editor::hierarchy(Node* node, mat4 ident) {
        

        if (node->editor_open)
            for (s32 i = 0; i < (s32)node->children.size(); ++i)
                hierarchy(node->children[i], ident);
    }

    void Editor::main(s32 width, s32 height, Node* scene) {
        mat4 ident;
        mat4_identity(&ident);

        this->width = width;
        this->height = height;

        render->rect(ident, v2{0,0}, v2{256,(f32)height}, v4{1,1,1,1});

        ImGuiViewport* viewport = ImGui::GetMainViewport();

        ImGui::SetNextWindowPos(viewport->Pos);
        ImGui::SetNextWindowSize(viewport->Size);
        ImGui::SetNextWindowViewport(viewport->ID);

        ImGui::Begin("editor");
        ImGui::End();

        if (ImGui::Begin("hierarchy")) {
            hierarchy(scene, ident);
        } ImGui::End();

        if (ImGui::Begin("game")) {
            ImGui::Text("hah you thought something was here");
        } ImGui::End();
    }
}
