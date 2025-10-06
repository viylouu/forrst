#define FST_EDITOR
#include <forrst.hh>

#include <core/render.hh>
#include <cstdlib>
#include <core/mat4.h>
#include <core/texture.h>

class FSTrenderer2d : public FSTcomponent {
public:
    v4 col;
    FSTtexture* tex;
    v4 sample;

    void init() {
        publics.push_back((FSTvarInfo){ &tex, "texture", FST_TYPEOF_REF });
        publics.push_back((FSTvarInfo){ &col, "tint (float)", FST_TYPEOF_VEC4 }); 
    }

    void render() {
        fst_render_tex(rstate, tex, parent->transf, 0,0,1,1, sample.x,sample.y,sample.z,sample.w, col.x,col.y,col.z,col.w);
    }
};

class game : public FSTgame {
public:
    FSTtexture* tex;

    void init() {
        tex = fst_texture_load("examples/texture/youresosilly.jpg");
    }

    void render() {
        fst_render_clear(rstate, .2,.4,.3,1); 

        scene->children.clear();

        srand(glfwGetTime()*10000000);
        for (s32 i = 0; i < 2048; ++i) {
            FSTnode* node = new FSTnode();
            FSTrenderer2d* comp = new FSTrenderer2d();
            comp->col = (v4){
                (rand()%256)/256.f,
                (rand()%256)/256.f,
                (rand()%256)/256.f,
                1};

            comp->tex = tex;
            comp->sample = (v4){
                (rand()%256)/256.f,
                (rand()%256)/256.f,
                (f32)tex->width * (rand()%256)/256.f,
                (f32)tex->height * (rand()%256)/256.f};

            node->addComponent(comp);
            scene->addChild(node);
            node->scale = (v3){
                (rand()%256)+64,
                (rand()%256)+64,
                1};

            node->pos = (v3){
                rand()%1440,
                rand()%1440,
                0};

            node->rot = (v3){
                (rand()%256)/256.f*3.14159265f,
                (rand()%256)/256.f*3.14159265f,
                (rand()%256)/256.f*3.14159265f
                };
        }
    }
};

FST_MAIN(game);
