#include "shader.hh"

#include <core/macros.h>
#include <core/auto/load_gl.h>
#include <GL/gl.h>

namespace fur {
    namespace shader {
        /*
         * [PART]
         */

        void shaderPart_unload(ShaderPart* part) {
            glDeleteShader(part->part);
            delete part;
        }

        char* shaderPart_loadSource(const char* path) {
            FILE* file = fopen(path, "rb");
            ERROR_IF(!file, "failed to open shader part at \"%s\"!\n", path);

            fseek(file, 0, SEEK_END);
            s64 size = ftell(file);
            rewind(file);

            char* buffer = (char*)malloc(size + 1);
            ERROR_IF(!buffer, "failed to alloc size for shader part at \"%s\"", path);

            fread(buffer, 1, size, file);
            fclose(file);

            buffer[size] = '\0';

            return buffer;
        }

        ShaderPart* shaderPart_loadFromSource(u32 type, const char** source) {
            u32 part = glCreateShader(type);
            glShaderSource(part, 1, source, 0);
            glCompileShader(part);

            s32 success = 0;
            glGetShaderiv(part, GL_COMPILE_STATUS, &success);
            if (!success) {
                s32 length = 0;
                glGetShaderiv(part, GL_INFO_LOG_LENGTH, &length);

                char* log = (char*)malloc(length);
                glGetShaderInfoLog(part, length, 0, log);

                printf("part compile error!\n%s\n", log);
                free(log);

                glDeleteShader(part);
                exit(1);
            }

            ShaderPart* out = new ShaderPart();
            out->part = part;

            return out;
        }

        /*
         * [SHADER]
         */

        s32 getUniform(Shader* shader, const char* name) {
            s32 uni = glGetUniformLocation(shader->shader, name);
            RETURN_IF(uni == -1, -1, "uniform not found / optimized out!\n");
            return uni;
        }

        void unload(Shader* shader) {
            glDeleteProgram(shader->shader);
            delete shader;
        }

        Shader* compileFromParts(ShaderPart** parts, u32 amount) {
            u32 shader = glCreateProgram();

            for (u32 i = 0; i < amount; ++i)
                glAttachShader(shader, (*(ShaderPart**)((char*)parts+sizeof(uptr)*i))->part);
            glLinkProgram(shader);

            s32 success = 0;
            glGetProgramiv(shader, GL_LINK_STATUS, &success);
            if (!success) {
                s32 length = 0;
                glGetProgramiv(shader, GL_INFO_LOG_LENGTH, &length);

                char* log = (char*)malloc(length);
                glGetProgramInfoLog(shader, length, 0, log);

                printf("shader compile error!\n%s\n", log);
                free(log);

                glDeleteProgram(shader);
                exit(1);
            }

            Shader* out = new Shader();
            out->shader = shader;
            out->parts = parts;
            out->part_amt = amount;

            return out;
        }

        Shader* loadFromParts(ShaderPart** parts, u32 amount) {
            return compileFromParts(parts, amount);
        }

        Shader* loadFromSource(const char** vert, const char** frag) {
            ShaderPart* vertex = shaderPart_loadFromSource(GL_VERTEX_SHADER, vert);
            ShaderPart* fragment = shaderPart_loadFromSource(GL_FRAGMENT_SHADER, frag);

            Shader* shader = compileFromParts((ShaderPart*[2]){ vertex, fragment }, 2);

            shaderPart_unload(vertex);
            shaderPart_unload(fragment);

            return shader;
        }

        Shader* load(const char* vert, const char* frag) {
            char* vertbuffer = shaderPart_loadSource(vert);
            char* fragbuffer = shaderPart_loadSource(frag);

            const char* vertsource = vertbuffer;
            const char* fragsource = fragbuffer;

            Shader* shader = loadFromSource(&vertsource, &fragsource);

            free(vertbuffer);
            free(fragbuffer);

            return shader;
        }
    }
}
