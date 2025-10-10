#include "render.hh"

#include <core/macros.h>
#include <core/auto/load_gl.h>
#include <GL/gl.h>
#include <core/shader.hh>
#include <core/mat4.h>
#include <core/texture.hh>

namespace fur {           
    /* table of contents:
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
     * [GL STRUCT FUNCS]
     */

    /* [gl struct 2d funcs] */

#define FUR_rSdInitGeneric(state,vert,frag)                                                       \
        state.generic.shader = shader::load(vert,frag);                                                  \
                                                                                                  \
        glGenBuffers(1, &state.generic.bo);                                                     \
        glBindBuffer(GL_TEXTURE_BUFFER, state.generic.bo);                                      \
        glBufferData(GL_TEXTURE_BUFFER, FUR_MAX_BUFFER_SIZE, NULL, GL_DYNAMIC_DRAW);              \
                                                                                                  \
        glGenTextures(1, &state.generic.tbo);                                                   \
        glBindTexture(GL_TEXTURE_BUFFER, state.generic.bo);                                     \
        glTexBuffer(GL_TEXTURE_BUFFER, GL_RGBA32F, state.generic.bo);                           \
                                                                                                  \
        state.generic.loc.insts     = glGetUniformLocation(state.generic.shader->shader, "insts");     \
        state.generic.loc.inst_size = glGetUniformLocation(state.generic.shader->shader, "inst_size"); \
        state.generic.loc.proj      = glGetUniformLocation(state.generic.shader->shader, "proj")
#define FUR_rSdEndGeneric(state)          \
        shader::unload(state.generic.shader);    \
        glDeleteTextures(1, &state.generic.tbo); \
        glDeleteBuffers(1, &state.generic.bo)
#define FUR_rSdDrawGeneric(obj) do {                                                                                \
        glUseProgram(obj.generic.shader->shader);                                                                          \
        glBindVertexArray(vao);                                                                                     \
                                                                                                                    \
        glUniformMatrix4fv(obj.generic.loc.proj, 1,0, proj2d);                                                             \
                                                                                                                    \
        glBindBuffer(GL_TEXTURE_BUFFER, obj.generic.bo);                                                                   \
        glBufferSubData(GL_TEXTURE_BUFFER, 0, batch.size() * sizeof(InstanceData), batch.data());                   \
                                                                                                                    \
        glActiveTexture(GL_TEXTURE0);                                                                               \
        glBindTexture(GL_TEXTURE_BUFFER, obj.generic.tbo);                                                                 \
        glUniform1i(obj.generic.loc.insts, 0);                                                                             \
                                                                                                                    \
        glUniform1i(obj.generic.loc.inst_size, sizeof(InstanceData) / 16);                                                 \
    } while(0)


    void Render::rSdRect_init() {
        FUR_rSdInitGeneric(sdRect, "data/eng/rect.vert", "data/eng/rect.frag");
    } void Render::rSdRect_end() {
        FUR_rSdEndGeneric(sdRect);
    } void Render::rSdRect_draw() {
        FUR_rSdDrawGeneric(sdRect);
        
        glDrawArraysInstanced(GL_TRIANGLES, 0,6, batch.size());
    }

    void Render::rSdTex_init() {
        FUR_rSdInitGeneric(sdTex, "data/eng/tex.vert", "data/eng/tex.frag");

        sdTex.loc.tex = glGetUniformLocation(sdTex.generic.shader->shader, "tex");
    } void Render::rSdTex_end() {
        FUR_rSdEndGeneric(sdTex);
    } void Render::rSdTex_draw() {
        FUR_rSdDrawGeneric(sdTex);

        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, batch_tex->glid);
        glUniform1i(sdTex.loc.tex, 1);

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

        nil = texture::load("data/eng/nil.png");
        ERROR_IF(!nil, "failed to load nil texture!\n");

        rSdRect_init();
        rSdTex_init();

        rSsCube_init();
        rSsModel_init();
    }

    Render::~Render() {
        rSdRect_end();
        rSdTex_end();

        rSsCube_end();
        rSsModel_end();

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
                rSdRect_draw(); break;
            case BatchType::BATCH_2D_TEX:
                rSdTex_draw(); break;
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
        //if (batch_targ != targ) flush();

        if (tex == NULL) {
            if (batch_tex != nil) flush();
            batch_tex = nil;
            printf("rendering a nil texture!\n");
        } else {
            if (batch_tex != tex) flush();
            batch_tex = tex;
        }

        batch_type = BATCH_2D_TEX;
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
