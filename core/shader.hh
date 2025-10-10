#ifndef FUR_SHADER_H
#define FUR_SHADER_H

#include <core/macros.h>

namespace fur {
    struct ShaderPart {
        u32 part;
    };

    struct Shader {
        u32 shader;
        ShaderPart** parts;
        u32 part_amt;
    };

    namespace shader {
        char*       shaderPart_loadSource(const char* path);
        ShaderPart* shaderPart_loadFromSource(u32 type, const char** source);
        void        shaderPart_unload(ShaderPart* part);

        Shader* compileFromParts(ShaderPart** parts, u32 amount);
        Shader* loadFromParts(ShaderPart** parts, u32 amount);
        Shader* loadFromSource(const char** vert, const char** frag);
        Shader* load(const char* vert, const char* frag);
        void    unload(Shader* shader);
    }
}

#endif
