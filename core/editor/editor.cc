#include "editor.hh"

#include <core/render.hh>
#include <GLFW/glfw3.h>
#include <core/node.hh>
#include <core/text.hh>
#include <cstdio>

namespace fur {
    namespace editor {
        struct EditorState {
            Font* font;
        };

        void* fur_editor_init() {
            EditorState* state = new EditorState();

            state->font = fur_text_loadFont("data/eng/font.png");

            return state;
        }

        void fur_editor_end(void* mstate) {
            EditorState* state = (EditorState*)mstate;
            
            fur_text_unloadFont(state->font);

            free(mstate);
        }

        s32 fur_editor_hierarchy(void* mstate, void* rstate, Node* node, mat4 ident, s32 y, s32 indent);
        s32 hierarchy(void* mstate, void* rstate, Node* node, mat4 ident, s32 y, s32 indent) {
            EditorState* state = (EditorState*)mstate;
            RenderState* rend = (RenderState*)rstate;

            if (y > -state->font->charH*2)
                fur_text_draw(NULL, state->font, ident, node->name, 2, 2+indent*state->font->charW*4,y+2, 0,0,0,1);

            for (s32 i = 0; i < (s32)node->children.size(); ++i) {
                y = fur_editor_hierarchy(mstate, rstate, node->children[i], ident, y + state->font->charH*2, indent+1);

                if (y > rend->height)
                    return y;
            }

            return y;
        }

        void main(asdflkj* state, Node* scene) {
            EditorState* state = (EditorState*)mstate;

            mat4 ident;
            fur_mat4_identity(&ident);

            s32 width,height;
            glfwGetWindowSize((GLFWwindow*)gstate, &width,&height);

            fur_render_rect(rstate, NULL, ident, 0,0,256,height, 1,1,1,1);

            hierarchy(state, rstate, scene, ident, 0,0);
        }
    }
}
