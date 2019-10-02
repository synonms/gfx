#pragma once

#include <glproxy\glproxy-exports.h>

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
                    GLPROXY_API static bool Compile(unsigned int shaderId, bool throwOnError = false);
                    GLPROXY_API static unsigned int Create(enumerators::ShaderType shaderType, bool throwOnError = false);
                    GLPROXY_API static void Delete(unsigned int shaderId, bool throwOnError = false);
                    GLPROXY_API static std::string GetLog(unsigned int shaderId);
                    GLPROXY_API static void SetSource(unsigned int shaderId, const std::string& sourceCode, bool throwOnError = false);
                };
            }
        }
    }
}
