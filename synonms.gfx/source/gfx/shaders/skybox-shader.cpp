#include "skybox-shader.h"

#include <gfx\shaders\shader-extensions.h>

#include <opengl\factories\shader-factory.h>
#include <opengl\state-manager.h>

using namespace synonms::gfx::transforms;
using namespace synonms::gfx::primitives;
using namespace synonms::gfx::shaders;
using namespace synonms::gfx::api;

SkyBoxShader::SkyBoxShader(const std::string& vertexShaderSource, const std::string& fragmentShaderSource)
{
    _shaderProgram = opengl::factories::ShaderFactory::Create(vertexShaderSource, fragmentShaderSource);
}

void SkyBoxShader::Render(const Matrix4x4& sceneRotationMatrix, const Matrix4x4& projectionMatrix, const opengl::Texture& skyBoxTexture, const Mesh& mesh)
{
    _shaderProgram->Use();

    ShaderExtensions::SetUniform(*_shaderProgram.get(), "vu_sceneRotationMatrix", sceneRotationMatrix);
    ShaderExtensions::SetUniform(*_shaderProgram.get(), "vu_projectionMatrix", projectionMatrix);

    ShaderExtensions::SetUniform(*_shaderProgram.get(), "fu_cubeMapTextureSlot", 0);
    opengl::Texture::ActivateSlot(0);
    skyBoxTexture.Bind();

    opengl::StateManager::DisableDepthTesting();

    mesh.Draw();

    opengl::StateManager::EnableDepthTesting();
}
