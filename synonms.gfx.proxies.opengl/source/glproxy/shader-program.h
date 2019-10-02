#pragma once

#include <glproxy\glproxy-exports.h>

#include <string>

namespace synonms
{
    namespace gfx
    {
        namespace proxies
        {
            namespace opengl
            {
                class ShaderProgram
                {
                public:
                    GLPROXY_API static void AttachShader(unsigned int programId, unsigned int shaderId, bool throwOnError = false);
                    GLPROXY_API static unsigned int Create(bool throwOnError = false);
                    GLPROXY_API static void Delete(unsigned int programId, bool throwOnError = false);
                    GLPROXY_API static int GetUniformLocation(unsigned int programId, const std::string& uniformName, bool throwOnError = false);
                    GLPROXY_API static void Link(unsigned int programId, bool throwOnError = false);
                    GLPROXY_API static void SetUniform(unsigned int location, int value, bool throwOnError = false);
                    GLPROXY_API static void SetUniform(unsigned int location, float value1, float value2, float value3, float value4, bool throwOnError = false);
                    GLPROXY_API static void Use(unsigned int programId, bool throwOnError = false);
                    GLPROXY_API static void Validate(unsigned int programId, bool throwOnError = false);
                };
            }
        }
    }
}
