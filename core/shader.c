#include "shader.h"

#include <core/macros.h>
#include <core/auto/load_gl.h>
#include <GL/gl.h>

/* table of contents:
 **** [PART]
 **** [SHADER]
 */

/*
 * [PART]
 */

char* fst_shaderPart_loadSource(const char* path) {
    FILE* file = fopen(path, "rb");
    ERROR_IF(!file, "failed to open shader part at \"%s\"!\n", path);

    fseek(file, 0, SEEK_END);
    s64 size = ftell(file);
    rewind(file);

    char* buffer = malloc(size + 1);
    ERROR_IF(!buffer, "failed to alloc size for shader part at \"%s\"", path);

    fread(buffer, 1, size, file);
    fclose(file);

    buffer[size] = '\0';

    return buffer;
}

FSTshaderPart* fst_shaderPart_loadFromSource(u32 type, const char** source) {
    u32 part = glCreateShader(type);
    glShaderSource(part, 1, source, 0);
    glCompileShader(part);

    s32 success = 0;
    glGetShaderiv(part, GL_COMPILE_STATUS, &success);
    if (!success) {
        s32 length = 0;
        glGetShaderiv(part, GL_INFO_LOG_LENGTH, &length);

        char* log = malloc(length);
        glGetShaderInfoLog(part, length, 0, log);

        printf("part compile error!\n%s\n", log);
        free(log);

        glDeleteShader(part);
        exit(1);
    }

    FSTshaderPart* out = malloc(sizeof(FSTshaderPart));
    out->part = part;

    return out;
}

void fst_shaderPart_unload(FSTshaderPart* part) {
    glDeleteShader(part->part);
    free(part);
}

/*
 * [SHADER]
 */

FSTshader* fst_shader_compileFromParts(FSTshaderPart** parts, u32 amount) {
    u32 shader = glCreateProgram();

    for (u32 i = 0; i < amount; ++i)
        glAttachShader(shader, (*(FSTshaderPart**)((char*)parts+sizeof(uptr)*i))->part);
    glLinkProgram(shader);

    s32 success = 0;
    glGetProgramiv(shader, GL_LINK_STATUS, &success);
    if (!success) {
        s32 length = 0;
        glGetProgramiv(shader, GL_INFO_LOG_LENGTH, &length);

        char* log = malloc(length);
        glGetProgramInfoLog(shader, length, 0, log);

        printf("shader compile error!\n%s\n", log);
        free(log);

        glDeleteProgram(shader);
        exit(1);
    }

    FSTshader* out = malloc(sizeof(FSTshader));
    out->shader = shader;
    out->parts = parts;
    out->part_amt = amount;

    return out;
}

inline FSTshader* fst_shader_loadFromParts(FSTshaderPart** parts, u32 amount) {
    return fst_shader_compileFromParts(parts, amount);
}

FSTshader* fst_shader_loadFromSource(const char** vert, const char** frag) {
    FSTshaderPart* vertex = fst_shaderPart_loadFromSource(GL_VERTEX_SHADER, vert);
    FSTshaderPart* fragment = fst_shaderPart_loadFromSource(GL_FRAGMENT_SHADER, frag);

    FSTshader* shader = fst_shader_compileFromParts((FSTshaderPart*[2]){ vertex, fragment }, 2);

    fst_shaderPart_unload(vertex);
    fst_shaderPart_unload(fragment);

    return shader;
}

FSTshader* fst_shader_load(const char* vert, const char* frag) {
    char* vertbuffer = fst_shaderPart_loadSource(vert);
    char* fragbuffer = fst_shaderPart_loadSource(frag);

    const char* vertsource = vertbuffer;
    const char* fragsource = fragbuffer;

    FSTshader* shader = fst_shader_loadFromSource(&vertsource, &fragsource);

    free(vertbuffer);
    free(fragbuffer);

    return shader;
}

void fst_shader_unload(FSTshader* shader) {
    glDeleteProgram(shader->shader);
    free(shader);
}
