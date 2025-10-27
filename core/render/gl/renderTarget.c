#include "renderTarget.h"

#include <render/gl/loader.h>
#include <core/data/api/gl/texture.h>

#include <core/macros.h>
#include <stdio.h>
#include <stdlib.h>

/* ====== FUNCS ====== */

FUR_gl_renderTarget* fur_renderTarget_gl_constr(FUR_renderTarget* agnostic, s32 width, s32 height) {
    u32 fbo;
    glGenFramebuffers(1, &fbo);
    glBindFramebuffer(GL_FRAMEBUFFER, fbo);

    FUR_gl_texture* gltex = NEW(FUR_gl_texture);

    glGenTextures(1, &gltex->id);
    glBindTexture(GL_TEXTURE_2D, gltex->id);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width,height, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glBindTexture(GL_TEXTURE_2D, 0);

    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, gltex->id, 0);

    GLenum drawbuf;
    glDrawBuffers(1, &drawbuf);

    u32 depth;
    glGenRenderbuffers(1, &depth);
    glBindRenderbuffer(GL_RENDERBUFFER, depth);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT24, width, height);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, depth);

    GLenum fbostatus = glCheckFramebufferStatus(GL_FRAMEBUFFER);
    WARN_RET_IF(fbostatus != GL_FRAMEBUFFER_COMPLETE, NULL, "framebuffer is not complete! status: 0x%x\n", fbostatus);

    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    FUR_gl_renderTarget* targ = NEW(FUR_gl_renderTarget);
    targ->agnostic = agnostic;
    targ->fbo = fbo;
    targ->depth = depth;

    agnostic->texture->spec = gltex;

    return targ;
}

void fur_renderTarget_gl_destr(FUR_gl_renderTarget* targ) {
    WARN_RETVOID_IF(!targ, "cannot destruct null gl render target!\n");

    FUR_renderTarget* agnost = CAST(FUR_renderTarget*, targ->agnostic);
    FUR_gl_texture* agltex = CAST(FUR_gl_texture*, agnost->texture->spec);

    glDeleteRenderbuffers(1, &targ->depth);
    glDeleteTextures(1, &agltex->id);
    glDeleteFramebuffers(1, &targ->fbo);

    free(targ);
}

void fur_renderTarget_gl_resize(FUR_gl_renderTarget* targ, s32 width, s32 height) {
    WARN_RETVOID_IF(!targ, "cannot resize null gl render target!\n");

    FUR_renderTarget* agnost = CAST(FUR_renderTarget*, targ->agnostic);
    FUR_gl_texture* agltex = CAST(FUR_gl_texture*, agnost->texture->spec);

    agnost->texture->width = width;
    agnost->texture->height = height;

    glBindTexture(GL_TEXTURE_2D, agltex->id);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
    glBindTexture(GL_TEXTURE_2D, 0);
    
    glBindRenderbuffer(GL_RENDERBUFFER, targ->depth);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT24, width, height);
    glBindRenderbuffer(GL_RENDERBUFFER, 0);
}
