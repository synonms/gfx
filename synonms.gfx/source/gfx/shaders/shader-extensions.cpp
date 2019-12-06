#include "shader-extensions.h"

using namespace synonms::gfx::api;
using namespace synonms::gfx::mathematics::linear;
using namespace synonms::gfx::shaders;

void ShaderExtensions::SetUniform(const opengl::ShaderProgram& shaderProgram, const std::string& uniformName, bool value)
{
    auto location = shaderProgram.GetUniformLocation(uniformName);
    opengl::ShaderProgram::SetUniformBool(location, value);
}

void ShaderExtensions::SetUniform(const opengl::ShaderProgram& shaderProgram, const std::string& uniformName, int value)
{
    auto location = shaderProgram.GetUniformLocation(uniformName);
    opengl::ShaderProgram::SetUniformInt(location, value);
}

void ShaderExtensions::SetUniform(const opengl::ShaderProgram& shaderProgram, const std::string& uniformName, float value)
{
    auto location = shaderProgram.GetUniformLocation(uniformName);
    opengl::ShaderProgram::SetUniformFloat(location, value);
}

void ShaderExtensions::SetUniform(const opengl::ShaderProgram& shaderProgram, const std::string& uniformName, const Vector3<float>& vector)
{
    auto location = shaderProgram.GetUniformLocation(uniformName);
    opengl::ShaderProgram::SetUniformVector3(location, vector.x, vector.y, vector.z);
}

void ShaderExtensions::SetUniform(const opengl::ShaderProgram& shaderProgram, const std::string& uniformName, const Vector4<float>& vector)
{
    auto location = shaderProgram.GetUniformLocation(uniformName);
    opengl::ShaderProgram::SetUniformVector4(location, vector.x, vector.y, vector.z, vector.w);
}

void ShaderExtensions::SetUniform(const opengl::ShaderProgram& shaderProgram, const std::string& uniformName, const Matrix3x3& matrix)
{
    auto location = shaderProgram.GetUniformLocation(uniformName);
    opengl::ShaderProgram::SetUniformMatrix3x3(location, matrix.Data());
}

void ShaderExtensions::SetUniform(const opengl::ShaderProgram& shaderProgram, const std::string& uniformName, const Matrix4x4& matrix)
{
    auto location = shaderProgram.GetUniformLocation(uniformName);
    opengl::ShaderProgram::SetUniformMatrix4x4(location, matrix.Data());
}
