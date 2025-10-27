#include "renderTarget.h"

#include <render/gl/loader.h>

#include <core/macros.h>
#include <stdio.h>
#include <stdlib.h>

/* ====== FUNCS ====== */

FUR_gl_renderTarget* fur_renderTarget_gl_constr(FUR_renderTarget* agnostic, s32 width, s32 height) {
    u32 fbo;
    glGenFramebuffers(1, &fbo);
    glBindFramebuffer(GL_FRAMEBUFFER, fbo);

    u32 tex;
    glGenTextures(1, &tex);
    glBindTexture(GL_TEXTURE_2D, tex);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width,height, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glBindTexture(GL_TEXTURE_2D, 0);

    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, tex, 0);

    u32 depth;
    glGenRenderbuffers(1, &depth);
    glBindRenderbuffer(GL_RENDERBUFFER, depth);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT24, width, height);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, depth);

    WARN_RET_IF(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE, NULL, "framebuffer is not complete!\n");

    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    FUR_gl_renderTarget* targ = NEW(FUR_gl_renderTarget);
    targ->agnostic = agnostic;
    targ->fbo = fbo;
    targ->tex = tex;
    targ->depth = depth;

    return targ;
}

void fur_renderTarget_gl_destr(FUR_gl_renderTarget* targ) {
    WARN_RETVOID_IF(!targ, "cannot destruct null gl render target!\n");

    glDeleteRenderbuffers(1, &targ->depth);
    glDeleteTextures(1, &targ->tex);
    glDeleteFramebuffers(1, &targ->fbo);

    free(targ);
}
