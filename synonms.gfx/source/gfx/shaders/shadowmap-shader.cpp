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

void ShadowmapShader::RenderOrthographic(const Matrix4x4& viewProjectionMatrix, const Matrix4x4& modelMatrix, const Mesh& mesh)
{
    _shaderProgram->Use();

    ShaderExtensions::SetUniform(*_shaderProgram.get(), "vu_viewProjectionMatrix", viewProjectionMatrix);
    ShaderExtensions::SetUniform(*_shaderProgram.get(), "vu_modelMatrix", modelMatrix);

    ShaderExtensions::SetUniform(*_shaderProgram.get(), "fu_isOrthographic", true);

    mesh.Draw();
}

void ShadowmapShader::RenderPerspective(const Matrix4x4& viewProjectionMatrix, const Matrix4x4& modelMatrix, float nearPlane, float farPlane, const Mesh& mesh)
{
    _shaderProgram->Use();

    ShaderExtensions::SetUniform(*_shaderProgram.get(), "vu_viewProjectionMatrix", viewProjectionMatrix);
    ShaderExtensions::SetUniform(*_shaderProgram.get(), "vu_modelMatrix", modelMatrix);

    ShaderExtensions::SetUniform(*_shaderProgram.get(), "fu_isOrthographic", false);
    ShaderExtensions::SetUniform(*_shaderProgram.get(), "fu_nearPlane", nearPlane);
    ShaderExtensions::SetUniform(*_shaderProgram.get(), "fu_farPlane", farPlane);

    mesh.Draw();
}

