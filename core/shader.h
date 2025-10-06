#ifndef FUR_SHADER_H
#define FUR_SHADER_H

#include <core/macros.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
    u32 part;
} FURshaderPart;

typedef struct {
    u32 shader;
    FURshaderPart** parts;
    u32 part_amt;
} FURshader;

char* fur_shaderPart_loadSource(const char* path);
FURshaderPart* fur_shaderPart_loadFromSource(u32 type, const char** source);
void fur_shaderPart_unload(FURshaderPart* part);

FURshader* fur_shader_compileFromParts(FURshaderPart** parts, u32 amount);
inline FURshader* fur_shader_loadFromParts(FURshaderPart** parts, u32 amount);
FURshader* fur_shader_loadFromSource(const char** vert, const char** frag);
FURshader* fur_shader_load(const char* vert, const char* frag);
void fur_shader_unload(FURshader* shader);

#ifdef __cplusplus
}
#endif

#endif
