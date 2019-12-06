#include "shader-factory.h"

#include <opengl\opengl-exception.h>
#include <opengl\shader.h>

#include <map>

using namespace synonms::gfx::api::opengl;
using namespace synonms::gfx::api::opengl::enumerators;
using namespace synonms::gfx::api::opengl::factories;

std::unique_ptr<ShaderProgram> ShaderFactory::Create(const std::string& vertexShaderSource, const std::string& fragmentShaderSource)
{
    auto shaderProgram = std::make_unique<opengl::ShaderProgram>();

    Shader vertexShader(opengl::enumerators::ShaderType::Vertex);
    vertexShader.SetSource(vertexShaderSource);
    if (!vertexShader.Compile())
    {
        throw OpenglException({ {0u, vertexShader.GetLog()} });
    }

    Shader fragmentShader(opengl::enumerators::ShaderType::Fragment);
    fragmentShader.SetSource(fragmentShaderSource);
    if (!fragmentShader.Compile())
    {
        throw OpenglException({ {1u, fragmentShader.GetLog()} });
    }

    shaderProgram->AttachShader(vertexShader.GetShaderId());
    shaderProgram->AttachShader(fragmentShader.GetShaderId());

    shaderProgram->Link();
    shaderProgram->Validate();

    return std::move(shaderProgram);
}
