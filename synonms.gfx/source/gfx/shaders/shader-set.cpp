#include "shader-set.h"

#include <glproxy\shader.h>
#include <glproxy\shader-program.h>

#include <sstream>

using namespace synonms::gfx::shaders;

class ShaderSet::Implementation 
{
public:
    unsigned int programId;
    unsigned int vertexShaderId;
    unsigned int fragmentShaderId;

    unsigned int CompileShader(proxies::opengl::enumerators::ShaderType shaderType, const std::string& source)
    {
        auto shaderId = proxies::opengl::Shader::Create(shaderType, true);

        proxies::opengl::Shader::SetSource(shaderId, source, true);

        if (!proxies::opengl::Shader::Compile(shaderId, true))
        {
            auto message = proxies::opengl::Shader::GetLog(shaderId);

            proxies::opengl::Shader::Delete(shaderId, true);

            throw std::exception(message.c_str());
        }

        return shaderId;
    }
};

ShaderSet::ShaderSet(const std::string& vertexShaderSource, const std::string& fragmentShaderSource)
{
    _implementation = std::make_unique<ShaderSet::Implementation>();

    _implementation->programId = proxies::opengl::ShaderProgram::Create(true);
    _implementation->vertexShaderId = _implementation->CompileShader(proxies::opengl::enumerators::ShaderType::Vertex, vertexShaderSource);
    _implementation->fragmentShaderId = _implementation->CompileShader(proxies::opengl::enumerators::ShaderType::Fragment, fragmentShaderSource);

    proxies::opengl::ShaderProgram::AttachShader(_implementation->programId, _implementation->vertexShaderId, true);
    proxies::opengl::ShaderProgram::AttachShader(_implementation->programId, _implementation->fragmentShaderId, true);

    proxies::opengl::ShaderProgram::Link(_implementation->programId, true);
    proxies::opengl::ShaderProgram::Validate(_implementation->programId, true);

    proxies::opengl::Shader::Delete(_implementation->vertexShaderId, true);
    proxies::opengl::Shader::Delete(_implementation->fragmentShaderId, true);
}

ShaderSet::~ShaderSet()
{
    proxies::opengl::ShaderProgram::Delete(_implementation->programId, false);
}

void ShaderSet::SetUniform(const std::string& uniformName, int value)
{
    auto location = proxies::opengl::ShaderProgram::GetUniformLocation(_implementation->programId, uniformName, true);
    proxies::opengl::ShaderProgram::SetUniform(location, value, true);
}

void ShaderSet::SetUniform(const std::string& uniformName, float value1, float value2, float value3, float value4)
{
    auto location = proxies::opengl::ShaderProgram::GetUniformLocation(_implementation->programId, uniformName, true);
    proxies::opengl::ShaderProgram::SetUniform(location, value1, value2, value3, value4, true);
}

std::string ShaderSet::ToString()
{
    std::stringstream stream;
    stream << "[ShaderSet: ProgramId " << _implementation->programId << ", VertexShaderId " << _implementation->vertexShaderId << ", FragmentShaderId " << _implementation->fragmentShaderId << "]";

    return stream.str();
}

void ShaderSet::Use()
{
    proxies::opengl::ShaderProgram::Use(_implementation->programId, true);
}


