#pragma once

#include <string>

#include <glproxy\enumerators\shader-type.h>

namespace synonms
{
    namespace gfx
    {
        namespace proxies
        {
            namespace opengl
            {
                class Shader
                {
                public:
                    static bool Compile(unsigned int shaderId, bool throwOnError = false);
                    static unsigned int Create(enumerators::ShaderType shaderType, bool throwOnError = false);
                    static void Delete(unsigned int shaderId, bool throwOnError = false);
                    static std::string GetLog(unsigned int shaderId);
                    static void SetSource(unsigned int shaderId, const std::string& sourceCode, bool throwOnError = false);
                };
            }
        }
    }
}
