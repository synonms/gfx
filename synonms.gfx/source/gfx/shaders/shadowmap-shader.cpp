#include "shadowmap-shader.h"

#include <gfx\shaders\shader-extensions.h>

#include <opengl\factories\shader-factory.h>

using namespace synonms::gfx::mathematics::linear;
using namespace synonms::gfx::primitives;
using namespace synonms::gfx::shaders;
using namespace synonms::gfx::api;

ShadowmapShader::ShadowmapShader(const std::string& vertexShaderSource, const std::string& fragmentShaderSource)
{
    _shaderProgram = opengl::factories::ShaderFactory::Create(vertexShaderSource, fragmentShaderSource);
}

void ShadowmapShader::Render(const Matrix4x4& modelViewProjectionMatrix, const Mesh& mesh)
{
    _shaderProgram->Use();

    ShaderExtensions::SetUniform(*_shaderProgram.get(), "vu_modelViewProjectionMatrix", modelViewProjectionMatrix);

    mesh.Draw();
}
