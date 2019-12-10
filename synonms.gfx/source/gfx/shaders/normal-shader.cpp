#include "normal-shader.h"

#include <gfx\shaders\shader-extensions.h>

#include <opengl\factories\shader-factory.h>

using namespace synonms::gfx::mathematics::linear;
using namespace synonms::gfx::primitives;
using namespace synonms::gfx::shaders;
using namespace synonms::gfx::api;

NormalShader::NormalShader(const std::string& vertexShaderSource, const std::string& fragmentShaderSource, const std::string& geometryShaderSource)
{
    _shaderProgram = opengl::factories::ShaderFactory::Create(vertexShaderSource, fragmentShaderSource, geometryShaderSource);
}

void NormalShader::Render(const Matrix4x4& projectionMatrix, const Matrix4x4& viewMatrix, const Matrix4x4& modelMatrix, const Matrix3x3& normalMatrix, const Mesh& mesh)
{
    _shaderProgram->Use();

    ShaderExtensions::SetUniform(*_shaderProgram.get(), "vu_projectionMatrix", projectionMatrix);
    ShaderExtensions::SetUniform(*_shaderProgram.get(), "vu_viewMatrix", viewMatrix);
    ShaderExtensions::SetUniform(*_shaderProgram.get(), "vu_modelMatrix", modelMatrix);
    ShaderExtensions::SetUniform(*_shaderProgram.get(), "vu_normalMatrix", normalMatrix);

    mesh.Draw();
}
