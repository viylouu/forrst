#include "texture.h"

#include <core/macros.h>
#include <stdio.h>
#include <stdlib.h>

#include <render/gl/loader.h>

#define STB_IMAGE_IMPLEMENTATION
#include <stb/stbimage.h>

/* ====== FUNCS ====== */

FUR_gl_texture* fur_gl_texture_loadFromData(FUR_texture* agnostic, u8* data, size_t size) {
    s32 w,h, c;
    u8* texdata = stbi_load_from_memory(data, size, &w,&h, &c,4);
    WARN_RET_IF(!texdata, NULL, "failed to load texture!\n");

    u32 id;
    glGenTextures(1, &id);
    glBindTexture(GL_TEXTURE_2D, id);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w,h, 0, GL_RGBA, GL_UNSIGNED_BYTE, texdata);

    glBindTexture(GL_TEXTURE_2D, 0);

    FUR_gl_texture* texture = NEW(FUR_gl_texture);
    texture->id = id;

    texture->agnostic = agnostic;
    CAST(FUR_texture*, texture->agnostic)->width = w;
    CAST(FUR_texture*, texture->agnostic)->height = h;

    return texture;
}

char* fur_gl_texture_loadData(const char* path, size_t* out_size) {
    FILE* file = fopen(path, "rb");
    WARN_RET_IF(!file, NULL, "failed to open shader at \"%s\"!\n", path);

    fseek(file, 0, SEEK_END);
    long size = ftell(file); // why is it long and not long long so i can use s64? idfk
    rewind(file);

    char* buffer = malloc(size);
    WARN_RET_IF(!buffer, (fclose(file), NULL), "failed to allocate size for the shader at \"%s\"!\n", path);

    fread(buffer, 1, size, file);
    fclose(file);

    *out_size = size;

    return buffer;
}

FUR_gl_texture* fur_gl_texture_load(FUR_texture* agnostic, const char* path) {
    size_t size;
    char* buf = fur_gl_texture_loadData(path, &size);
    WARN_RET_IF(!buf, NULL, "failed to read texture at \"%s\"!\n", path);

    FUR_gl_texture* texture = fur_gl_texture_loadFromData(agnostic, (u8*)buf, size);
    TRY_FREE(buf);

    WARN_RET_IF(!texture, NULL, "failed to load texture at \"%s\"!\n", path);

    return texture;
}

void fur_gl_texture_unload(FUR_gl_texture* texture) {
    WARN_RETVOID_IF(!texture, "cannot unload null texture!\n");

    glDeleteTextures(1, &texture->id);
    free(texture);
}
