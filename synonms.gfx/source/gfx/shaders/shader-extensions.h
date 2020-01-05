#pragma once

#include <gfx/transforms/matrix3x3.h>
#include <gfx/transforms/matrix4x4.h>
#include <gfx/geometry/point3.h>
#include <gfx/geometry/vector3.h>
#include <gfx/geometry/vector4.h>

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
                static void SetUniform(const api::opengl::ShaderProgram& shaderProgram, const std::string& uniformName, unsigned int value);
                static void SetUniform(const api::opengl::ShaderProgram& shaderProgram, const std::string& uniformName, float value);
                static void SetUniform(const api::opengl::ShaderProgram& shaderProgram, const std::string& uniformName, const geometry::Point3<float>& point);
                static void SetUniform(const api::opengl::ShaderProgram& shaderProgram, const std::string& uniformName, const geometry::Vector3<float>& vector);
                static void SetUniform(const api::opengl::ShaderProgram& shaderProgram, const std::string& uniformName, const geometry::Vector4<float>& vector);
                static void SetUniform(const api::opengl::ShaderProgram& shaderProgram, const std::string& uniformName, const transforms::Matrix3x3& matrix);
                static void SetUniform(const api::opengl::ShaderProgram& shaderProgram, const std::string& uniformName, const transforms::Matrix4x4& matrix);
            };
        }
    }
}