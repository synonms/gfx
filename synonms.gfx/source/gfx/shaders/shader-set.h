#pragma once

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
                ShaderSet(const std::string& vertexShaderSource, const std::string& fragmentShaderSource);
                ~ShaderSet();

                unsigned int Id();
                void SetUniform(const std::string& uniformName, int value);
                void SetUniform(const std::string& uniformName, float value1, float value2, float value3, float value4);
                void SetUniformMatrix(const std::string& uniformName, const float* value);
                std::string ToString();
                void Use();

            private:
                class Implementation;
                std::unique_ptr<Implementation> _implementation;
            };
        }
    }
}