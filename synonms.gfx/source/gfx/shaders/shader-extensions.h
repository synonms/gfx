#pragma once

#include <gfx/mathematics/linear/matrix3x3.h>
#include <gfx/mathematics/linear/matrix4x4.h>
#include <gfx/mathematics/linear/vector3.h>
#include <gfx/mathematics/linear/vector4.h>

#include <opengl\shader-program.h>

#include <memory>
#include <string>

namespace synonms
{
    namespace gfx
    {
        namespace shaders
        {
            class ShaderExtensions
            {
            public:
                static void SetUniform(const api::opengl::ShaderProgram& shaderProgram, const std::string& uniformName, bool value);
                static void SetUniform(const api::opengl::ShaderProgram& shaderProgram, const std::string& uniformName, int value);
                static void SetUniform(const api::opengl::ShaderProgram& shaderProgram, const std::string& uniformName, float value);
                static void SetUniform(const api::opengl::ShaderProgram& shaderProgram, const std::string& uniformName, const mathematics::linear::Vector3<float>& vector);
                static void SetUniform(const api::opengl::ShaderProgram& shaderProgram, const std::string& uniformName, const mathematics::linear::Vector4<float>& vector);
                static void SetUniform(const api::opengl::ShaderProgram& shaderProgram, const std::string& uniformName, const mathematics::linear::Matrix3x3& matrix);
                static void SetUniform(const api::opengl::ShaderProgram& shaderProgram, const std::string& uniformName, const mathematics::linear::Matrix4x4& matrix);
            };
        }
    }
}