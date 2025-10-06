#include "editor.hh"

#include <core/render.hh>
#include <GLFW/glfw3.h>
#include <core/node.hh>
#include <core/text.hh>
#include <cstdio>

typedef struct {
    FURfont* font;
} FUReditorState;

void* fur_editor_init() {
    FUReditorState* state = new FUReditorState();

    state->font = fur_text_loadFont("data/eng/font.png");

    return state;
}

void fur_editor_end(void* mstate) {
    FUReditorState* state = (FUReditorState*)mstate;
    
    fur_text_unloadFont(state->font);

    free(mstate);
}

s32 fur_editor_hierarchy(void* mstate, void* rstate, FURnode* node, mat4 ident, s32 y, s32 indent);
s32 fur_editor_hierarchy(void* mstate, void* rstate, FURnode* node, mat4 ident, s32 y, s32 indent) {
    FUReditorState* state = (FUReditorState*)mstate;
    
    char buf[1024];
    sprintf(buf, "%*s%s", indent*2,"", node->name);

    const char* cbuf = buf;

    fur_text_draw(rstate, NULL, state->font, ident, cbuf, 2, 2,y+2, 0,0,0,1);

    for (s32 i = 0; i < (s32)node->children.size(); ++i)
        y = fur_editor_hierarchy(mstate, rstate, node->children[i], ident, y + state->font->charH*2, indent+1);

    return y;
}

void fur_editor(void* mstate, void* gstate, void* rstate, FURnode* scene) {
    FUReditorState* state = (FUReditorState*)mstate;

    mat4 ident;
    fur_mat4_identity(&ident);

    s32 width,height;
    glfwGetWindowSize((GLFWwindow*)gstate, &width,&height);

    fur_render_rect(rstate, NULL, ident, 0,0,256,height, 1,1,1,1);

    fur_editor_hierarchy(state, rstate, scene, ident, 0,0);
}
