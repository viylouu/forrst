#ifndef FST_SHADER_H
#define FST_SHADER_H

#include <core/macros.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
    u32 part;
} FSTshaderPart;

typedef struct {
    u32 shader;
    FSTshaderPart** parts;
    u32 part_amt;
} FSTshader;

char* fst_shaderPart_loadSource(const char* path);
FSTshaderPart* fst_shaderPart_loadFromSource(u32 type, const char** source);
void fst_shaderPart_unload(FSTshaderPart* part);

FSTshader* fst_shader_compileFromParts(FSTshaderPart** parts, u32 amount);
inline FSTshader* fst_shader_loadFromParts(FSTshaderPart** parts, u32 amount);
FSTshader* fst_shader_loadFromSource(const char** vert, const char** frag);
FSTshader* fst_shader_load(const char* vert, const char* frag);
void fst_shader_unload(FSTshader* shader);

#ifdef __cplusplus
}
#endif

#endif
