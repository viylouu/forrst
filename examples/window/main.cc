#define FUR_EDITOR
#include <furry.hh>

#include <core/render.hh>
#include <cstdlib>
#include <core/mat4.h>

class FURrenderer2d : public FURcomponent {
public:
    v4 col;

    void init() {
        publics.push_back((FURvarInfo){ &col, "color (float)", FUR_TYPEOF_VEC4 }); 
    }

    void render() {
        fur_render_rect(rstate, NULL, parent->transf, 0,0,1,1, col.x,col.y,col.z,col.w);
    }
};

class game : public FURgame {
public:
    s32 tick;

    void init() {
        //for (s32 i = 0; i < 16384; ++i) {
            FURnode* node = new FURnode();
            FURrenderer2d* comp = new FURrenderer2d();
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
        fur_render_clear(rstate, NULL, .2,.4,.3,1);       
    }
};

FUR_MAIN(game);
