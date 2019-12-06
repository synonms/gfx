#include "shader.h"

#include <GL\glew.h>

#include <utility>

using namespace synonms::gfx::api::opengl;
using namespace synonms::gfx::api::opengl::enumerators;

Shader::Shader(ShaderType shaderType)
{
    _shaderId = glCreateShader(static_cast<unsigned int>(shaderType));
}

Shader::Shader(Shader&& other) noexcept
    : _shaderId(std::exchange(other._shaderId, 0))
{
}

Shader& Shader::operator=(Shader&& other) noexcept
{
    _shaderId = std::exchange(other._shaderId, 0);

    return *this;
}

Shader::~Shader()
{
    if (_shaderId > 0) {
        glDeleteShader(_shaderId);
    }
}


bool Shader::Compile() const
{
    glCompileShader(_shaderId);

    int result;
    glGetShaderiv(_shaderId, GL_COMPILE_STATUS, &result);

    return result == GL_TRUE;
}

std::string Shader::GetLog() const
{
    int length;
    glGetShaderiv(_shaderId, GL_INFO_LOG_LENGTH, &length);

    char* message = (char*)alloca(length * sizeof(char));
    glGetShaderInfoLog(_shaderId, length, &length, message);

    return message;
}

void Shader::SetSource(const std::string& sourceCode) const
{
    auto sourceData = sourceCode.c_str();

    glShaderSource(_shaderId, 1, &sourceData, nullptr);
}

