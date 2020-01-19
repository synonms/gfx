#include "pbr-shader.h"

#include <gfx\shaders\shader-extensions.h>
#include <gfx\mathematics\maths-helper.h>

#include <opengl\factories\shader-factory.h>

using namespace synonms::gfx::materials;
using namespace synonms::gfx::mathematics;
using namespace synonms::gfx::primitives;
using namespace synonms::gfx::shaders;
using namespace synonms::gfx::transforms;
using namespace synonms::gfx::api;

PBRShader::PBRShader(const std::string& vertexShaderSource, const std::string& fragmentShaderSource)
{
    _shaderProgram = opengl::factories::ShaderFactory::Create(vertexShaderSource, fragmentShaderSource);
}

void PBRShader::Render(const PBRShaderData& data)
{
    _shaderProgram->Use();

    ShaderExtensions::SetUniform(*_shaderProgram.get(), "vu_viewMatrix", data.viewMatrix);
    ShaderExtensions::SetUniform(*_shaderProgram.get(), "vu_projectionMatrix", data.projectionMatrix);

    auto modelMatrix = data.meshInstance.GetModelMatrix();
    auto normalMatrix = Matrix4x4::CreateNormalFrom(modelMatrix);

    ShaderExtensions::SetUniform(*_shaderProgram.get(), "vu_modelMatrix", modelMatrix);
    ShaderExtensions::SetUniform(*_shaderProgram.get(), "vu_normalMatrix", normalMatrix);

    ShaderExtensions::SetUniform(*_shaderProgram.get(), "vu_camera.position", data.camera.position);

    ShaderExtensions::SetUniform(*_shaderProgram.get(), "vu_lights[0].type", static_cast<int>(data.light.Type));
    ShaderExtensions::SetUniform(*_shaderProgram.get(), "vu_lights[0].position", data.light.position);
    ShaderExtensions::SetUniform(*_shaderProgram.get(), "vu_lights[0].direction", data.light.GetDirection());
    ShaderExtensions::SetUniform(*_shaderProgram.get(), "vu_lights[0].viewProjectionMatrix", data.light.shadowMapProjectionMatrix * data.light.GetViewMatrix());

    auto uniforms = _shaderProgram->GetActiveUniforms();

    auto& material = data.meshInstance.GetMaterial();
    auto currentTextureSlot = 0;

    currentTextureSlot = SetUniforms(material.Albedo ? material.Albedo.get() : nullptr, currentTextureSlot, "albedo", uniforms);
    currentTextureSlot = SetUniforms(material.Normal ? material.Normal.get() : nullptr, currentTextureSlot, "normal", uniforms);
    currentTextureSlot = SetUniforms(material.Metallic ? material.Metallic.get() : nullptr, currentTextureSlot, "metallic", uniforms);
    currentTextureSlot = SetUniforms(material.Roughness ? material.Roughness.get() : nullptr, currentTextureSlot, "roughness", uniforms);
    currentTextureSlot = SetUniforms(material.AmbientOcclusion ? material.AmbientOcclusion.get() : nullptr, currentTextureSlot, "ambientOcclusion", uniforms);

    if (data.light.shadowMapDepthTexture)
    {
        ShaderExtensions::SetUniform(*_shaderProgram.get(), "fu_lights[0].shadowMapTextureSlot", currentTextureSlot);
        opengl::Texture::ActivateSlot(currentTextureSlot);
        data.light.shadowMapDepthTexture->Bind();
        currentTextureSlot++;
    }

    ShaderExtensions::SetUniform(*_shaderProgram.get(), "fu_cubeMapTextureSlot", currentTextureSlot);
    opengl::Texture::ActivateSlot(currentTextureSlot);
    data.skyBoxTexture.Bind();

    ShaderExtensions::SetUniform(*_shaderProgram.get(), "fu_material.specularColourF0", material.SpecularColourF0);
    ShaderExtensions::SetUniform(*_shaderProgram.get(), "fu_material.isShadowReceiverOnly", material.isShadowReceiverOnly);

    ShaderExtensions::SetUniform(*_shaderProgram.get(), "fu_lights[0].type", static_cast<int>(data.light.Type));
    ShaderExtensions::SetUniform(*_shaderProgram.get(), "fu_lights[0].radiance", data.light.radiance);

    data.meshInstance.GetMesh().Draw();
}

unsigned int PBRShader::SetUniforms(opengl::Texture* texture, int currentTextureSlot, const std::string& name, const std::vector<std::string>& uniforms) const
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