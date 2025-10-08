#define FUR_EDITOR
#include <furry.hh>

#include <core/render.hh>
#include <cstdlib>
#include <core/mat4.h>
#include <core/texture.h>
#include <cstring>
#include <cstdlib>
#include <cstdio>

class FURrenderer2d : public FURcomponent {
public:
    v4 col;
    FURtexture* tex;
    v4 sample;
    FURrenderTarget* targ;

    FURrenderer2d() : targ(NULL) {}

    void init() {
        publics.push_back((FURvarInfo){ &tex, "texture", FUR_TYPEOF_REF });
        publics.push_back((FURvarInfo){ &col, "tint (float)", FUR_TYPEOF_VEC4 }); 
        publics.push_back((FURvarInfo){ &targ, "render target", FUR_TYPEOF_REF });
    }

    void render() {
        if (rstate)
            fur_render_rect(rstate, targ, /*tex,*/ parent->transf, 0,0,1,1, /*sample.x,sample.y,sample.z,sample.w,*/ col.x,col.y,col.z,col.w);
        else
            printf("no rstate?\n");
    }
};

class game : public FURgame {
public:
    FURtexture* tex;
    char buf[256];
    FURrenderTarget* targ;
    mat4 transf;

    void init() {
        tex = fur_texture_load("examples/texture/youresosilly.jpg");

        targ = fur_renderTarget_make(480,270);

        for (s32 i = 0; i < 1000; ++i) {
            FURnode* node = new FURnode();
            FURrenderer2d* comp = new FURrenderer2d();
            comp->targ = targ;
            node->addComponent(comp);

            sprintf(buf, "cone #%d", i);
            node->name = (char*)malloc(strlen(buf) + 1);
            std::strcpy(node->name, buf);

            scene->addChild(node);
        }

        fur_mat4_identity(&transf);
    }

    void end() {
        fur_texture_unload(tex);

        for (s32 i = 0; i < (s32)scene->children.size(); ++i)
            delete[] scene->children[i]->name;

        fur_renderTarget_unload(targ);
    }

    void update(float delta) {
        //printf("%d\n", (s32)(1.f/delta));
    }

    void render() {
        fur_render_clear(rstate, targ, .2,.4,.3,1); 

        srand(glfwGetTime()*10000000);
        for (s32 i = 0; i < (s32)scene->children.size(); ++i) {
            FURnode* node = scene->children[i];
            FURrenderer2d* comp = (FURrenderer2d*)scene->children[i]->components[0];

            /*comp->col = (v4){
                (rand()%256)/256.f,
                (rand()%256)/256.f,
                (rand()%256)/256.f,
                1};*/
            comp->col = (v4){1,0,0,1};

            //comp->tex = tex;
            /*comp->sample = (v4){
                (rand()%256)/256.f,
                (rand()%256)/256.f,
                (f32)tex->width * (rand()%256)/256.f,
                (f32)tex->height * (rand()%256)/256.f};*/

            /*node->scale = (v3){
                (rand()%256)+64,
                (rand()%256)+64,
                1};*/
            node->scale = (v3){16,16,1};

            /*node->pos = (v3){
                rand()%480,
                rand()%270,
                0};*/
            node->pos = (v3){0,0,0};

            /*node->rot = (v3){
                (rand()%256)/256.f*3.14159265f,
                (rand()%256)/256.f*3.14159265f,
                (rand()%256)/256.f*3.14159265f
                };*/
            node->rot = (v3){0,0,0};
        }

        //fur_render_rect(rstate, targ, transf, 0,0,16,16,1,0,0,1);

        fur_render_renderTarget(rstate, NULL, targ, transf, 0,0,FUR_WIDTH,FUR_HEIGHT,0,0,targ->width,targ->height, 1,1,1,1);
    }
};

FUR_MAIN(game);
