#include "render.hh"

#include <core/macros.h>
#include <core/auto/load_gl.h>
#include <GL/gl.h>
#include <core/shader.hh>
#include <core/mat4.h>
#include <core/texture.hh>
#include <vector>

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
        Shader* shad; u32 bo, tbo
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

    enum BatchType {
        BATCH_2D_RECT,
        BATCH_2D_TEX,
        BATCH_SS_CUBE,
        BATCH_SS_MODEL
    };

    /*
     * [GL STRUCT FUNCS]
     */

    /* [gl struct 2d funcs] */

#define FUR_r2dInitGeneric(state,vert,frag)                                              \
        state->shader = shader::load(vert,frag);                                         \
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
#define FUR_r2dEndGeneric(state)          \
        shader::unload(state->shader);    \
        glDeleteTextures(1, &state->tbo); \
        glDeleteBuffers(1, &state->bo)
#define FUR_r2dDrawGeneric(obj) do {                                                                                \
        FUR_useTarget(state->batch_targ);                                                                           \
                                                                                                                    \
        glUseProgram(obj->shader->shader);                                                                          \
        glBindVertexArray(state->vao);                                                                              \
                                                                                                                    \
        glUniformMatrix4fv(obj->loc.proj, 1,0, state->proj2d);                                                      \
                                                                                                                    \
        glBindBuffer(GL_TEXTURE_BUFFER, obj->bo);                                                                   \
        glBufferSubData(GL_TEXTURE_BUFFER, 0, state->batch.size() * sizeof(TnstanceData), batch.data());            \
                                                                                                                    \
        glActiveTexture(GL_TEXTURE0);                                                                               \
        glBindTexture(GL_TEXTURE_BUFFER, obj->tbo);                                                                 \
        glUniform1i(obj->loc.insts, 0);                                                                             \
                                                                                                                    \
        glUniform1i(obj->loc.inst_size, sizeof(InstanceData) / 16);                                                 \
    } while(0)


    void Render::r2dRect_init() {
        FUR_r2dInitGeneric(sdRect, "data/eng/rect.vert", "data/eng/rect.frag");
    } void Render::r2dRect_end() {
        FUR_r2dEndGeneric(sdRect);
    } void Render::r2dRect_draw() {
        FUR_r2dDrawGeneric(sdRect);
        
        glDrawArraysInstanced(GL_TRIANGLES, 0,6, sdRect->batch.size());
    }

    void Render::r2dTex_init() {
        FUR_r2dInitGeneric(sdTex, "data/eng/tex.vert", "data/eng/tex.frag");

        sdTex->loc.tex = glGetUniformLocation(sdTex->shader->shader, "tex");
    } void Render::r2dTex_end() {
        FUR_r2dEndGeneric(sdTex);
    } void Render::r2dTex_draw() {
        FUR_r2dDrawGeneric(sdTex);

        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, batch_tex->glid);
        glUniform1i(sdTex->loc.tex, 1);

        glDrawArraysInstanced(GL_TRIANGLES, 0,6, batch.size());
    }

    /* [gl struct spritestack funcs] */
    void Render::rSsCube_init() {
    } void Render::rSsCube_end() {
    } void Render::rSsCube_draw() {
    }

    void Render::rSsModel_init() {
    } void Render::rSsModel_end() {
    } void Render::rSsModel_draw() {
    }

    /*
     * [INIT/END]
     */

    Render::Render() {
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        glDepthMask(GL_TRUE);
        glDepthFunc(GL_LEQUAL);

        glGenVertexArrays(1, &vao);

        fur_r2dRect_init(&sdRect);
        fur_r2dTex_init(&sdTex);

        fur_rSsCube_init(&ssCube);
        fur_rSsModel_init(&ssModel);
    }

    Render::~Render() {
        fur_r2dRect_end(&sdRect);
        fur_r2dTex_end(&sdTex);

        fur_rSsCube_end(&ssCube);
        fur_rSsModel_end(&ssModel);

        glDeleteVertexArrays(1, &vao);
    }

    /*
     * [UPDATE]
     */

    void Render::resize(s32 width, s32 height) {
        this->width = width;
        this->height = height;
    }

    /*
     * [FUNCS]
     */

    /* [funcs generic] */
    void Render::flush() {
        if (batch.size() == 0)
            return;

        switch(batch_type) {
            case BatchType::BATCH_2D_RECT:
                r2dRect_draw(); break;
            case BatchType::BATCH_2D_TEX:
                r2dTex_draw(); break;
            case BatchType::BATCH_SS_CUBE:
                rSsCube_draw(); break;
            case BatchType::BATCH_SS_MODEL:
                rSsModel_draw(); break;
        }

        batch.clear();
    }

    void Render::clear(v4 col) {
        glClearColor(col.x,col.y,col.z,col.w);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }

    /* [funcs 2d] */
    void Render::rect(mat4 transf, v2 pos, v2 size, v4 col) {
        if (batch_type != BATCH_2D_RECT) flush();
        if (batch.size() >= FUR_MAX_BATCH_SIZE) flush();
        //if (batch_targ != targ) flush();

        batch_type = BATCH_2D_RECT;
        //state->batch_targ = targ;
        batch_tex = NULL;

        InstanceData inst;

        std::copy(transf,transf+16,inst.transf);

        inst.x = pos.x;
        inst.y = pos.y;
        inst.w = size.x;
        inst.h = size.y;
        inst.r = col.x;
        inst.g = col.y;
        inst.b = col.z;
        inst.a = col.w;

        batch.push_back(inst);
    }

    void Render::tex(Texture* tex, mat4 transf, v2 pos, v2 size, v4 sample, v4 col) {
        if (batch_type != BATCH_2D_TEX) flush();
        if (batch.size() >= FUR_MAX_BATCH_SIZE) flush();
        if (batch_tex != tex) flush();
        //if (batch_targ != targ) flush();

        batch_type = BATCH_2D_TEX;
        batch_tex = tex;
        //state->batch_targ = targ;

        InstanceData inst;

        std::copy(transf,transf+16,inst.transf);

        inst.x = pos.x;
        inst.y = pos.y;
        inst.w = size.x;
        inst.h = size.y;
        inst.r = col.x;
        inst.g = col.y;
        inst.b = col.z;
        inst.a = col.w;

        if (tex) {
            inst.sx = sample.x / (f32)tex->width;
            inst.sy = sample.y / (f32)tex->height;
            inst.sw = sample.z / (f32)tex->width;
            inst.sh = sample.w / (f32)tex->height;
        } else {
            /*if(targ) {
                inst.sx = sample.x / (f32)targ->width;
                inst.sy = sample.y / (f32)targ->height;
                inst.sw = sample.z / (f32)targ->width;
                inst.sh = sample.w / (f32)targ->height;
            } else {*/
                inst.sx = sample.x / width;
                inst.sy = sample.y / height;
                inst.sw = sample.z / width;
                inst.sh = sample.w / height;
            //}
        }

        batch.push_back(inst);
    }
}
