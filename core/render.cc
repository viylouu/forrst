#include <core/macros.h>
#include "render.hh"
#include <core/auto/load_gl.h>
#include <GL/gl.h>
#include <core/shader.h>
#include <core/mat4.h>
#include <core/texture.h>

namespace fur {           
    /* table of contents:
     **** [GL STRUCTS]
     **** **** [gl struct 2d]
     **** **** [gl struct spritestack]
     **** [GL STRUCT FUNCS]
     **** **** [gl struct 2d funcs]
     **** **** [gl struct spritestack funcs]
     **** [INIT/END]
     **** [UPDATE]
     **** [FUNCS]
     **** **** [funcs generic]
     **** **** [funcs 2d]
     */

    /*
     * [GL STRUCTS]
     *
     * this is the data for opengl to use
     * very silly
     */

#define FUR_genericInitEnd(name)        \
        void name##_init(void* data); \
        void name##_end(void* data)

    /* [gl struct 2d] */
#define FUR_r2dGeneric() \
        Shader* shader; u32 bo, tbo
#define FUR_r2dGenericLoc() \
        s32 inst_size; s32 insts; s32 proj

    struct r2dRect {
        FUR_r2dGeneric();
        struct {
            FUR_r2dGenericLoc();
        } loc;
    };

    struct r2dTex {
        FUR_r2dGeneric();
        struct {
            FUR_r2dGenericLoc();
            s32 tex;
        } loc;
    };

    /* [gl struct spritestack] */
#define FUR_rSsGeneric() \
        FURshader* shad; u32 bo, tbo
    // if this is too big... idgaf no it isnt
#define FUR_rSsGenericLoc() \
        s32 inst_size, insts, proj, cam_rot, cam_pos, cam_z, cam_tilt, cam_scale

    struct rSsCube {
        FUR_rSsGeneric();
        struct {
            FUR_rSsGenericLoc();
        } loc;
    };

    struct rSsModel {
        FUR_rSsGeneric();
        struct {
            FUR_rSsGenericLoc();
            s32 tex;
        } loc;
    };

    /*
     * [some shi]
     */

    struct InstanceData {
        f32 x,y,w,h;
        f32 r,g,b,a;
        f32 sx,sy,sw,sh;
        mat4 transf;
    };

    enum class BatchType : u8 {
        BATCH_2D_RECT,
        BATCH_2D_TEX,
        BATCH_SS_CUBE,
        BATCH_SS_MODEL
    };

    /*
     * [STATE]
     */

    struct RenderState {
        // shit ass garbage vao
        u32 vao;

        s32 width, height;

        std::vector<InstanceData> batch;
        BatchType batch_type;
        Texture* batch_tex;

        mat4 proj2d;

        struct r2dRect rect;
        struct r2dTex tex;

        struct rSsCube ssCube;
        struct rSsModel ssModel;
    };


#define FUR_genericInitEnd(name)        \
        void fur_##name##_init(void* data); \
        void fur_##name##_end(void* data)

    /* [gl struct 2d] */
    FUR_genericInitEnd(r2dRect);
    FUR_genericInitEnd(r2dTex);

    /* [gl struct spritestack] */
    FUR_genericInitEnd(rSsCube);
    FUR_genericInitEnd(rSsModel);

    /*
     * [GL STRUCT FUNCS]
     */

    /* [gl struct 2d funcs] */

#define FUR_r2dInitGeneric(vert,frag)                                                \
        state->shader = fur_shader_load(vert,frag);                                      \
                                                                                         \
        glGenBuffers(1, &state->bo);                                                     \
        glBindBuffer(GL_TEXTURE_BUFFER, state->bo);                                      \
        glBufferData(GL_TEXTURE_BUFFER, FUR_MAX_BUFFER_SIZE, NULL, GL_DYNAMIC_DRAW);     \
                                                                                         \
        glGenTextures(1, &state->tbo);                                                   \
        glBindTexture(GL_TEXTURE_BUFFER, state->bo);                                     \
        glTexBuffer(GL_TEXTURE_BUFFER, GL_RGBA32F, state->bo);                           \
                                                                                         \
        state->loc.insts     = glGetUniformLocation(state->shader->shader, "insts");     \
        state->loc.inst_size = glGetUniformLocation(state->shader->shader, "inst_size"); \
        state->loc.proj      = glGetUniformLocation(state->shader->shader, "proj")
#define FUR_r2dEndGeneric()           \
        fur_shader_unload(state->shader); \
        glDeleteTextures(1, &state->tbo); \
        glDeleteBuffers(1, &state->bo)
#define FUR_r2dDrawGeneric(obj) do {                                                                            \
        FUR_useTarget(state->batch_targ);                                                                           \
                                                                                                                    \
        glUseProgram(obj->shader->shader);                                                                          \
        glBindVertexArray(state->vao);                                                                              \
                                                                                                                    \
        glUniformMatrix4fv(obj->loc.proj, 1,0, state->proj2d);                                                      \
                                                                                                                    \
        glBindBuffer(GL_TEXTURE_BUFFER, obj->bo);                                                                   \
        glBufferSubData(GL_TEXTURE_BUFFER, 0, state->batch.size() * sizeof(FURinstanceData), state->batch.data());  \
                                                                                                                    \
        glActiveTexture(GL_TEXTURE0);                                                                               \
        glBindTexture(GL_TEXTURE_BUFFER, obj->tbo);                                                                 \
        glUniform1i(obj->loc.insts, 0);                                                                             \
                                                                                                                    \
        glUniform1i(obj->loc.inst_size, sizeof(FURinstanceData) / 16);                                              \
    } while(0)


    void fur_r2dRect_init(void* data) {
        FUR_r2dRect* state = (FUR_r2dRect*)data;

        FUR_r2dInitGeneric("data/eng/rect.vert", "data/eng/rect.frag");
    } void fur_r2dRect_end(void* data) {
        FUR_r2dRect* state = (FUR_r2dRect*)data;

        FUR_r2dEndGeneric();
    } void fur_r2dRect_draw(void* data, void* obj) {
        FURrenderState* state = (FURrenderState*)data;
        FUR_r2dRect* rect = (FUR_r2dRect*)obj;

        FUR_r2dDrawGeneric(rect);
        
        glDrawArraysInstanced(GL_TRIANGLES, 0,6, state->batch.size());
    }

    void fur_r2dTex_init(void* data) {
        FUR_r2dTex* state = (FUR_r2dTex*)data;

        FUR_r2dInitGeneric("data/eng/tex.vert", "data/eng/tex.frag");

        state->loc.tex = glGetUniformLocation(state->shader->shader, "tex");
    } void fur_r2dTex_end(void* data) {
        FUR_r2dTex* state = (FUR_r2dTex*)data;

        FUR_r2dEndGeneric();
    } void fur_r2dTex_draw(void* data, void* obj) {
        FURrenderState* state = (FURrenderState*)data;
        FUR_r2dTex* tex = (FUR_r2dTex*)obj;

        FUR_r2dDrawGeneric(tex);

        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, state->batch_tex->glid);
        glUniform1i(tex->loc.tex, 1);

        glDrawArraysInstanced(GL_TRIANGLES, 0,6, state->batch.size());
    }

    /* [gl struct spritestack funcs] */
    void fur_rSsCube_init(void* data) {
    } void fur_rSsCube_end(void* data) {
    } void fur_rSsCube_draw(void* data, void* obj) {
    }

    void fur_rSsModel_init(void* data) {
    } void fur_rSsModel_end(void* data) {
    } void fur_rSsModel_draw(void* data, void* obj) {
    }

    /*
     * [INIT/END]
     */

    Render::Render() {
        FURrenderState* state = new FURrenderState();

        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        glDepthMask(GL_TRUE);
        glDepthFunc(GL_LEQUAL);

        glGenVertexArrays(1, &state->vao);

        fur_r2dRect_init(&state->rect);
        fur_r2dTex_init(&state->tex);

        fur_rSsCube_init(&state->ssCube);
        fur_rSsModel_init(&state->ssModel);

        return state;
    }

    Render::~Render() {
        FURrenderState* state = (FURrenderState*)data;

        fur_r2dRect_end(&state->rect);
        fur_r2dTex_end(&state->tex);

        fur_rSsCube_end(&state->ssCube);
        fur_rSsModel_end(&state->ssModel);

        glDeleteVertexArrays(1, &state->vao);

        free(state);
    }

    /*
     * [UPDATE]
     */

    void Render::resize(void* data, s32 width, s32 height) {
        FURrenderState* state = (FURrenderState*)data;
        
        state->width = width;
        state->height = height;
    }

    /*
     * [FUNCS]
     */

    /* [funcs generic] */
    void Render::flush(void* data) {
        FURrenderState* state = (FURrenderState*)data;

        if (state->batch.size() == 0)
            return;

        switch(state->batch_type) {
            case FUR_BATCH_2D_RECT:
                fur_r2dRect_draw(data, &state->rect); break;
            case FUR_BATCH_2D_TEX:
                fur_r2dTex_draw(data, &state->tex); break;
            case FUR_BATCH_SS_CUBE:
                fur_rSsCube_draw(data, &state->ssCube); break;
            case FUR_BATCH_SS_MODEL:
                fur_rSsModel_draw(data, &state->ssModel); break;
        }

        state->batch.clear();
    }

    void Render::clear(void* data, FURrenderTarget* targ, f32 r, f32 g, f32 b, f32 a) {
        FURrenderState* state = (FURrenderState*)data;

        FUR_useTarget(targ);

        glClearColor(r,g,b,a);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }

    /* [funcs 2d] */
    void Render::rect(void* data, FURrenderTarget* targ, mat4 transf, f32 x, f32 y, f32 w, f32 h, f32 r, f32 g, f32 b, f32 a) {
        FURrenderState* state = (FURrenderState*)data;

        if (state->batch_type != FUR_BATCH_2D_RECT) fur_render_flush(data);
        if (state->batch.size() >= FUR_MAX_BATCH_SIZE) fur_render_flush(data);
        if (state->batch_targ != targ) fur_render_flush(data);

        state->batch_type = FUR_BATCH_2D_RECT;
        state->batch_targ = targ;
        state->batch_tex = NULL;

        FURinstanceData inst;

        std::copy(transf,transf+16,inst.transf);

        inst.x = x;
        inst.y = y;
        inst.w = w;
        inst.h = h;
        inst.r = r;
        inst.g = g;
        inst.b = b;
        inst.a = a;

        state->batch.push_back(inst);
    }

    void Render::tex(void* data, FURrenderTarget* targ, FURtexture* tex, mat4 transf, f32 x, f32 y, f32 w, f32 h, f32 sx, f32 sy, f32 sw, f32 sh, f32 r, f32 g, f32 b, f32 a) {
        FURrenderState* state = (FURrenderState*)data;

        if (state->batch_type != FUR_BATCH_2D_TEX) fur_render_flush(data);
        if (state->batch.size() >= FUR_MAX_BATCH_SIZE) fur_render_flush(data);
        if (state->batch_tex != tex) fur_render_flush(data);
        if (state->batch_targ != targ) fur_render_flush(data);

        state->batch_type = FUR_BATCH_2D_TEX;
        state->batch_tex = tex;
        state->batch_targ = targ;

        FURinstanceData inst;

        std::copy(transf,transf+16,inst.transf);

        inst.x = x;
        inst.y = y;
        inst.w = w;
        inst.h = h;
        inst.r = r;
        inst.g = g;
        inst.b = b;
        inst.a = a;

        if (tex) {
            inst.sx = sx / (f32)tex->width;
            inst.sy = sy / (f32)tex->height;
            inst.sw = sw / (f32)tex->width;
            inst.sh = sh / (f32)tex->height;
        } else {
            if(targ) {
                inst.sx = sx / (f32)targ->width;
                inst.sy = sy / (f32)targ->height;
                inst.sw = sw / (f32)targ->width;
                inst.sh = sh / (f32)targ->height;
            } else {
                inst.sx = sx / state->width;
                inst.sy = sy / state->height;
                inst.sw = sw / state->width;
                inst.sh = sh / state->height;
            }
        }

        state->batch.push_back(inst);
    }
}
