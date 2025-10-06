#define FST_EDITOR
#include <forrst.hh>

#include <core/render.hh>
#include <cstdlib>
#include <core/mat4.h>

class FSTrenderer2d : public FSTcomponent {
public:
    v4 col;

    void init() {
        publics.push_back((FSTvarInfo){ &col, "color (float)", FST_TYPEOF_VEC4 }); 
    }

    void render() {
        fst_render_rect(rstate, NULL, parent->transf, 0,0,1,1, col.x,col.y,col.z,col.w);
    }
};

class game : public FSTgame {
public:
    s32 tick;

    void init() {
        //for (s32 i = 0; i < 16384; ++i) {
            FSTnode* node = new FSTnode();
            FSTrenderer2d* comp = new FSTrenderer2d();
            comp->col = (v4){1,0,0,1};
            node->addComponent(comp);
            scene->addChild(node);
            node->scale = (v3){64,64,1};
            node->pos = (v3){512,512,0};
            node->rot.z = 45;
        //}
        tick = 0;
    }

    void render() {
        srand(++tick);
        fst_render_clear(rstate, NULL, .2,.4,.3,1);       
    }
};

FST_MAIN(game);
