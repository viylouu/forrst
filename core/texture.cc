#include "texture.hh"

#define STB_IMAGE_IMPLEMENTATION
#include <stb/stbimage.h>

#include <core/macros.h>
#include <core/auto/load_gl.h>

namespace fur {
    namespace texture {
        void unload(Texture* tex) {
            glDeleteTextures(1, &tex->glid);
            delete tex;
        }

        Texture* make(s32 width, s32 height) {
            u32 id;
            glGenTextures(1, &id);
            glBindTexture(GL_TEXTURE_2D, id);

            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);

            glBindTexture(GL_TEXTURE_2D, 0);

            Texture* tex = new Texture();
            tex->glid = id;
            tex->width = width;
            tex->height = height;

            return tex;
        }

        Texture* loadFromData(u8* data, s64 size) {
            s32 w,h,c;
            u8* texdata = stbi_load_from_memory(data, size, &w,&h,&c, 4);
            RETURN_IF(!texdata, (stbi_image_free(texdata), (Texture*)NULL), "failed to load texture!\n");

            u32 id;
            glGenTextures(1, &id);
            glBindTexture(GL_TEXTURE_2D, id);

            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w,h, 0, GL_RGBA, GL_UNSIGNED_BYTE, texdata);

            glBindTexture(GL_TEXTURE_2D, 0);

            stbi_image_free(texdata);

            Texture* tex = new Texture();
            tex->glid = id;
            tex->width = w;
            tex->height = h;

            return tex;
        }

        char* loadData(const char* path, s64* outsize) {
            FILE* file = fopen(path, "rb");
            // mm yes very clean
            RETURN_IF(!file, (fclose(file), (char*)NULL), "failed to load texture at \"%s\"!\n", path);

            fseek(file, 0, SEEK_END);
            s64 size = ftell(file);     
            rewind(file);

            char* buffer = (char*)malloc(size);
            RETURN_IF(!buffer, (fclose(file), (char*)NULL), "failed to allocate size for the texture at \"%s\"!\n", path);

            fread(buffer, 1, size, file);
            fclose(file);

            *outsize = size;

            return buffer;
        }

        Texture* load(const char* path) {
            s64 size;
            char* buf = loadData(path, &size);
            RETURN_IF(!buf, (free(buf), (Texture*)NULL), "failed to read file at \"%s\"!\n", path);

            Texture* tex = loadFromData((u8*)buf, size);
            free(buf);

            RETURN_IF(!tex, NULL, "failed to load texture at \"%s\"!\n", path);

            return tex;
        }
    }
}
