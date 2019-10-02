#pragma once

#include <gfx\exports.h>

#include <memory>
#include <string>

namespace synonms
{
    namespace gfx
    {
        namespace shaders
        {
            class ShaderSet
            {
            public:
                SYNONMS_GFX_API ShaderSet(const std::string& vertexShaderSource, const std::string& fragmentShaderSource);
                SYNONMS_GFX_API ~ShaderSet();

                SYNONMS_GFX_API unsigned int Id();
                SYNONMS_GFX_API void SetUniform(const std::string& uniformName, int value);
                SYNONMS_GFX_API void SetUniform(const std::string& uniformName, float value1, float value2, float value3, float value4);
                SYNONMS_GFX_API std::string ToString();
                SYNONMS_GFX_API void Use();

            private:
                class Implementation;
                std::unique_ptr<Implementation> _implementation;
            };
        }
    }
}