#include "shader.h"

#include <core/macros.h>
#include <render/gl/loader.h>

#include <stdlib.h>
#include <stdio.h>

/* ====== FUNCS ====== */

u32 fur_gl_sShader_loadFromSource(u32 type, const char** source) {
    u32 shader = glCreateShader(type);
    glShaderSource(shader, 1, source, 0);
    glCompileShader(shader);

    s32 success = 0;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success) {
        s32 length = 0;
        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &length);

        char* log = malloc(length);
        glGetShaderInfoLog(shader, length, 0, log);

        printf("shader compile error!\n%s\n", log);
        free(log);

        glDeleteShader(shader);
        exit(1);
    }

    return shader;
}

u32 fur_gl_program_compile(u32* shaders, u32 amount) {
    u32 program = glCreateProgram();

    for (u32 i = 0; i < amount; ++i)
        glAttachShader(program, shaders[i]);
    glLinkProgram(program);

    s32 success = 0;
    glGetProgramiv(program, GL_LINK_STATUS, &success);
    if (!success) {
        s32 length = 0;
        glGetProgramiv(program, GL_INFO_LOG_LENGTH, &length);

        char* log = malloc(length);
        glGetProgramInfoLog(program, length, 0, log);

        printf("shader program compile error!\n%s\n", log);
        free(log);

        glDeleteProgram(program);
        exit(1);
    }
    
    return program;
}

FUR_gl_shader* fur_gl_shader_loadFromSource(FUR_shader* agnostic, const char** vert, const char** frag) {
    u32 vertex = fur_gl_sShader_loadFromSource(GL_VERTEX_SHADER, vert);
    u32 fragment = fur_gl_sShader_loadFromSource(GL_FRAGMENT_SHADER, frag);

    u32 sshaders[2] = { vertex, fragment };
    u32 program = fur_gl_program_compile(sshaders, 2);

    glDeleteShader(vertex);
    glDeleteShader(fragment);

    FUR_gl_shader* shader = NEW(FUR_gl_shader);
    shader->agnostic = agnostic;

    shader->program = program;

    return shader;
}

char* fur_gl_shader_loadSource(const char* path) {
    FILE* file = fopen(path, "rb");
    if (!file) { 
        printf("failed to open shader at \"%s\"!\n", path); 
        exit(1); 
    }

    fseek(file, 0, SEEK_END);
    long size = ftell(file); // why is it long and not long long so i can use s64? idfk
    rewind(file);

    char* buffer = malloc(size + 1);
    if (!buffer) {
        fclose(file);
        printf("failed to allocate size for the shader at \"%s\"!\n", path);
        exit(1);
    }

    fread(buffer, 1, size, file);
    fclose(file);

    buffer[size] = '\0';

    return buffer;
}

FUR_gl_shader* fur_gl_shader_load(FUR_shader* agnostic, const char* vert, const char* frag) {
    char* vbuf = fur_gl_shader_loadSource(vert);
    char* fbuf = fur_gl_shader_loadSource(frag);

    ERROR_IF(!vbuf, "failed to read shader at \"%s\"!\n", vert);
    ERROR_IF(!fbuf, "failed to read shader at \"%s\"!\n", frag);

    const char* vsrc = vbuf;
    const char* fsrc = fbuf;

    FUR_gl_shader* shader = fur_gl_shader_loadFromSource(agnostic, &vsrc, &fsrc);

    free(vbuf);
    free(fbuf);

    return shader;
}

void fur_gl_shader_unload(FUR_gl_shader* shader) {
    free(shader);
}
