#include "deferred-gbuffer-shader.h"

#include <gfx\mathematics\maths-helper.h>
#include <gfx\shaders\shader-extensions.h>

#include <opengl\factories\shader-factory.h>
#include <opengl\texture.h>

using namespace synonms::gfx::mathematics;
using namespace synonms::gfx::primitives;
using namespace synonms::gfx::shaders;

using namespace synonms::gfx::api;

DeferredGBufferShader::DeferredGBufferShader(const std::string& vertexShaderSource, const std::string& fragmentShaderSource)
{
    _shaderProgram = opengl::factories::ShaderFactory::Create(vertexShaderSource, fragmentShaderSource);
}

void DeferredGBufferShader::Render(const DeferredGBufferShaderUniforms& data, const Mesh& mesh)
{
    _shaderProgram->Use();

    auto uniforms = _shaderProgram->GetActiveUniforms();

    auto currentTextureSlot = 0;

    currentTextureSlot = SetUniforms(data.ShaderMaterial.Albedo ? data.ShaderMaterial.Albedo.get() : nullptr, currentTextureSlot, "albedo", uniforms);
    currentTextureSlot = SetUniforms(data.ShaderMaterial.Normal ? data.ShaderMaterial.Normal.get() : nullptr, currentTextureSlot, "normal", uniforms);
    currentTextureSlot = SetUniforms(data.ShaderMaterial.Metallic ? data.ShaderMaterial.Metallic.get() : nullptr, currentTextureSlot, "metallic", uniforms);
    currentTextureSlot = SetUniforms(data.ShaderMaterial.Roughness ? data.ShaderMaterial.Roughness.get() : nullptr, currentTextureSlot, "roughness", uniforms);
    currentTextureSlot = SetUniforms(data.ShaderMaterial.AmbientOcclusion ? data.ShaderMaterial.AmbientOcclusion.get() : nullptr, currentTextureSlot, "ambientOcclusion", uniforms);

    ShaderExtensions::SetUniform(*_shaderProgram.get(), "vu_modelMatrix", data.ModelMatrix);
    ShaderExtensions::SetUniform(*_shaderProgram.get(), "vu_viewMatrix", data.ViewMatrix);
    ShaderExtensions::SetUniform(*_shaderProgram.get(), "vu_projectionMatrix", data.ProjectionMatrix);
    ShaderExtensions::SetUniform(*_shaderProgram.get(), "vu_normalMatrix", data.NormalMatrix);

    mesh.Draw();
}

unsigned int DeferredGBufferShader::SetUniforms(opengl::Texture* texture, int currentTextureSlot, const std::string& name, const std::vector<std::string>& uniforms) const
{
    auto textureSlotName = "fu_material." + name + "TextureSlot";
    auto presentName = "fu_material." + name + "Present";

    if (std::find(std::begin(uniforms), std::end(uniforms), textureSlotName) == std::end(uniforms))
    {
        return currentTextureSlot;
    }

    ShaderExtensions::SetUniform(*_shaderProgram.get(), textureSlotName, currentTextureSlot);
    ShaderExtensions::SetUniform(*_shaderProgram.get(), presentName, texture != nullptr);

    if (texture != nullptr) {
        opengl::Texture::ActivateSlot(currentTextureSlot);
        texture->Bind();
        currentTextureSlot++;
    }

    return currentTextureSlot;
}