#pragma once

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
                    static void AttachShader(unsigned int programId, unsigned int shaderId, bool throwOnError = false);
                    static unsigned int Create(bool throwOnError = false);
                    static void Delete(unsigned int programId, bool throwOnError = false);
                    static int GetUniformLocation(unsigned int programId, const std::string& uniformName, bool throwOnError = false);
                    static void Link(unsigned int programId, bool throwOnError = false);
                    static void SetUniform(unsigned int location, int value, bool throwOnError = false);
                    static void SetUniform(unsigned int location, float value1, float value2, float value3, float value4, bool throwOnError = false);
                    static void SetUniformMatrix(unsigned int location, const float* value, bool throwOnError = false);
                    static void Use(unsigned int programId, bool throwOnError = false);
                    static void Validate(unsigned int programId, bool throwOnError = false);
                };
            }
        }
    }
}
