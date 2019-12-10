#include "shader-factory.h"

#include <opengl\opengl-exception.h>
#include <opengl\shader.h>

#include <map>

using namespace synonms::gfx::api::opengl;
using namespace synonms::gfx::api::opengl::enumerators;
using namespace synonms::gfx::api::opengl::factories;

std::unique_ptr<ShaderProgram> ShaderFactory::Create(const std::string& vertexShaderSource, const std::string& fragmentShaderSource, const std::string& geometryShaderSource)
{
    auto shaderProgram = std::make_unique<opengl::ShaderProgram>();

    Shader vertexShader(opengl::enumerators::ShaderType::Vertex);
    vertexShader.SetSource(vertexShaderSource);
    if (!vertexShader.Compile())
    {
        auto message = vertexShader.GetLog();
        throw OpenglException({ {0u, message} });
    }
    shaderProgram->AttachShader(vertexShader.GetShaderId());

    Shader fragmentShader(opengl::enumerators::ShaderType::Fragment);
    fragmentShader.SetSource(fragmentShaderSource);
    if (!fragmentShader.Compile())
    {
        auto message = fragmentShader.GetLog();
        throw OpenglException({ {1u, message} });
    }
    shaderProgram->AttachShader(fragmentShader.GetShaderId());

    if (!geometryShaderSource.empty())
    {
        Shader geometryShader(opengl::enumerators::ShaderType::Geometry);
        geometryShader.SetSource(geometryShaderSource);
        if (!geometryShader.Compile())
        {
            auto message = geometryShader.GetLog();
            throw OpenglException({ {0u, message} });
        }
        shaderProgram->AttachShader(geometryShader.GetShaderId());
    }

    shaderProgram->Link();
    shaderProgram->Validate();

    return std::move(shaderProgram);
}
