#include "shader-program.h"

#include <opengl\opengl-exception.h>

#include <GL\glew.h>

#include <utility>

using namespace synonms::gfx::api::opengl;

ShaderProgram::ShaderProgram()
{
    _programId = glCreateProgram();
}

ShaderProgram::ShaderProgram(ShaderProgram&& other) noexcept
    : _programId(std::exchange(other._programId, 0))
{
}

ShaderProgram& ShaderProgram::operator=(ShaderProgram&& other) noexcept
{
    _programId = std::exchange(other._programId, 0);

    return *this;
}

ShaderProgram::~ShaderProgram()
{
    if (_programId > 0) {
        glDeleteProgram(_programId);
    }
}


void ShaderProgram::AttachShader(unsigned int shaderId) const
{
    glAttachShader(_programId, shaderId);
}

std::vector<std::string> ShaderProgram::GetActiveUniforms() const
{
    int noOfActiveUniforms;
    glGetProgramiv(_programId, GL_ACTIVE_UNIFORMS, &noOfActiveUniforms);

    GLint size; // size of the variable
    GLenum type; // type of the variable (float, vec3 or mat4, etc)
    const GLsizei bufSize = 64; // maximum name length
    GLchar name[bufSize]; // variable name in GLSL
    GLsizei length; // name length

    std::vector<std::string> results;

    for (auto i = 0u; i < noOfActiveUniforms; i++)
    {
        glGetActiveUniform(_programId, i, bufSize, &length, &size, &type, name);

        results.push_back(name);
    }

    return results;
}

int ShaderProgram::GetUniformLocation(const std::string& uniformName) const
{
    return glGetUniformLocation(_programId, uniformName.c_str());
}

void ShaderProgram::Link() const
{
    glLinkProgram(_programId);
}

void ShaderProgram::Use() const
{
    glUseProgram(_programId);
}

void ShaderProgram::Validate() const
{
    glValidateProgram(_programId);

    int validationStatus;
    glGetProgramiv(_programId, GL_VALIDATE_STATUS, &validationStatus);

    if (validationStatus != GL_TRUE) {
        throw OpenglException("Shader is invalid");
    }
}


void ShaderProgram::SetUniformBool(unsigned int location, bool value)
{
    glUniform1i(location, static_cast<int>(value));
}

void ShaderProgram::SetUniformFloat(unsigned int location, float value)
{
    glUniform1f(location, value);
}

void ShaderProgram::SetUniformInt(unsigned int location, int value)
{
    glUniform1i(location, value);
}

void ShaderProgram::SetUniformUnsignedInt(unsigned int location, unsigned int value)
{
    glUniform1ui(location, value);
}

void ShaderProgram::SetUniformVector3(unsigned int location, float value1, float value2, float value3)
{
    glUniform3f(location, value1, value2, value3);
}

void ShaderProgram::SetUniformVector4(unsigned int location, float value1, float value2, float value3, float value4)
{
    glUniform4f(location, value1, value2, value3, value4);
}

void ShaderProgram::SetUniformMatrix3x3(unsigned int location, const float* value)
{
    glUniformMatrix3fv(location, 1, GL_FALSE, value);
}

void ShaderProgram::SetUniformMatrix4x4(unsigned int location, const float* value)
{
    glUniformMatrix4fv(location, 1, GL_FALSE, value);
}
