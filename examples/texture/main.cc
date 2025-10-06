#define FST_EDITOR
#include <forrst.hh>

#include <core/render.hh>
#include <cstdlib>
#include <core/mat4.h>
#include <core/texture.h>
#include <cstring>
#include <cstdlib>

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
    char buf[256];

    void init() {
        tex = fst_texture_load("examples/texture/youresosilly.jpg");

        for (s32 i = 0; i < 1024; ++i) {
            FSTnode* node = new FSTnode();
            node->addComponent(new FSTrenderer2d());
            
            sprintf(buf, "cone #%d", i);
            node->name = (char*)malloc(strlen(buf) + 1);
            std::strcpy(node->name, buf);

            scene->addChild(node);
        }
    }

    void end() {
        fst_texture_unload(tex);

        for (s32 i = 0; i < scene->children.size(); ++i)
            delete[] scene->children[i]->name;
    }

    void update(float delta) {
        printf("%d\n", (s32)(1.f/delta));
    }

    void render() {
        fst_render_clear(rstate, .2,.4,.3,1); 
        
        srand(glfwGetTime()*10000000);
        for (s32 i = 0; i < scene->children.size(); ++i) {
            FSTnode* node = scene->children[i];
            FSTrenderer2d* comp = (FSTrenderer2d*)scene->children[i]->components[0];

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
