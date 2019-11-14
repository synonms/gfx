#pragma once

#include <gfx/mathematics/linear/matrix3x3.h>
#include <gfx/mathematics/linear/matrix4x4.h>
#include <gfx/mathematics/linear/vector3.h>
#include <gfx/mathematics/linear/vector4.h>

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
                virtual ~ShaderSet();

                void SetUniform(const std::string& uniformName, bool value);
                void SetUniform(const std::string& uniformName, int value);
                void SetUniform(const std::string& uniformName, float value);
                void SetUniform(const std::string& uniformName, const mathematics::linear::Vector3<float>& vector);
                void SetUniform(const std::string& uniformName, const mathematics::linear::Vector4<float>& vector);
                void SetUniform(const std::string& uniformName, const mathematics::linear::Matrix3x3& matrix);
                void SetUniform(const std::string& uniformName, const mathematics::linear::Matrix4x4& matrix);
                std::string ToString();
                void Use();

            private:
                class Implementation;
                std::unique_ptr<Implementation> _implementation;
            };
        }
    }
}