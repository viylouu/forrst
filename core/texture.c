#include "texture.h"

#define STB_IMAGE_IMPLEMENTATION
#include <stb/stbimage.h>

#include <core/macros.h>
#include <core/auto/load_gl.h>

void fst_texture_unload(FSTtexture* tex) {
    glDeleteTextures(1, &tex->glid);
    free(tex);
}

FSTtexture* fst_texture_make(s32 width, s32 height) {
    u32 id;
    glGenTextures(1, &id);
    glBindTexture(GL_TEXTURE_2D, id);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);

    glBindTexture(GL_TEXTURE_2D, 0);

    FSTtexture* tex = malloc(sizeof(FSTtexture));
    tex->glid = id;
    tex->width = width;
    tex->height = height;

    return tex;
}

FSTtexture* fst_texture_loadFromData(u8* data, s64 size) {
    s32 w,h,c;
    u8* texdata = stbi_load_from_memory(data, size, &w,&h,&c, 4);
    ERROR_IF(!texdata, "failed to load texture!\n");

    u32 id;
    glGenTextures(1, &id);
    glBindTexture(GL_TEXTURE_2D, id);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w,h, 0, GL_RGBA, GL_UNSIGNED_BYTE, texdata);

    glBindTexture(GL_TEXTURE_2D, 0);

    FSTtexture* tex = malloc(sizeof(FSTtexture));
    tex->glid = id;
    tex->width = w;
    tex->height = h;

    return tex;
}

char* fst_texture_loadData(const char* path, s64* outsize) {
    FILE* file = fopen(path, "rb");
    if (!file) { printf("failed to load texture at \"%s\"!\n", path); exit(1); }

    fseek(file, 0, SEEK_END);
    s64 size = ftell(file);     
    rewind(file);

    char* buffer = malloc(size);
    ERROR_IF(!buffer, "failed to allocate size for the texture at \"%s\"!\n", path);

    fread(buffer, 1, size, file);
    fclose(file);

    *outsize = size;

    return buffer;
}

FSTtexture* fst_texture_load(const char* path) {
    s64 size;
    char* buf = fst_texture_loadData(path, &size);
    ERROR_IF(!buf, "failed to read file at \"%s\"!\n", path);

    FSTtexture* tex = fst_texture_loadFromData((u8*)buf, size);
    free(buf);

    ERROR_IF(!tex, "failed to load texture at \"%s\"!\n", path);

    return tex;
}
