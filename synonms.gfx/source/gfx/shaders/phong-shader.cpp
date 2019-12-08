#include "phong-shader.h"

#include <gfx\mathematics\maths-helper.h>
#include <gfx\shaders\shader-extensions.h>

#include <opengl\factories\shader-factory.h>
#include <opengl\texture.h>

using namespace synonms::gfx::mathematics;
using namespace synonms::gfx::primitives;
using namespace synonms::gfx::shaders;

using namespace synonms::gfx::api;

PhongShader::PhongShader(const std::string& vertexShaderSource, const std::string& fragmentShaderSource)
{
    _shaderProgram = opengl::factories::ShaderFactory::Create(vertexShaderSource, fragmentShaderSource);
}

void PhongShader::Render(const PhongShaderUniforms& uniforms, const Mesh& mesh)
{
    _shaderProgram->Use();

    auto isDiffuseTextureEnabled = uniforms.ShaderMaterial.IsTextureEnabled(0);
    auto isSpecularTextureEnabled = uniforms.ShaderMaterial.IsTextureEnabled(1);
    auto isEmissiveTextureEnabled = uniforms.ShaderMaterial.IsTextureEnabled(2);

    if (isDiffuseTextureEnabled) uniforms.ShaderMaterial.ActivateTexture(0);
    if (isSpecularTextureEnabled) uniforms.ShaderMaterial.ActivateTexture(1);
    if (isEmissiveTextureEnabled) uniforms.ShaderMaterial.ActivateTexture(2);

    if (uniforms.ShaderLight.shadowMapDepthTexture)
    {
        opengl::Texture::ActivateSlot(3);
        uniforms.ShaderLight.shadowMapDepthTexture->Bind();
    }

    ShaderExtensions::SetUniform(*_shaderProgram.get(), "vu_modelMatrix", uniforms.ModelMatrix);
    ShaderExtensions::SetUniform(*_shaderProgram.get(), "vu_viewMatrix", uniforms.ViewMatrix);
    ShaderExtensions::SetUniform(*_shaderProgram.get(), "vu_projectionMatrix", uniforms.ProjectionMatrix);
    ShaderExtensions::SetUniform(*_shaderProgram.get(), "vu_normalMatrix", uniforms.NormalMatrix);

    ShaderExtensions::SetUniform(*_shaderProgram.get(), "vu_lights[0].type", static_cast<int>(uniforms.ShaderLight.Type));
    ShaderExtensions::SetUniform(*_shaderProgram.get(), "vu_lights[0].isEnabled", uniforms.ShaderLight.isEnabled);
    ShaderExtensions::SetUniform(*_shaderProgram.get(), "vu_lights[0].position", uniforms.ShaderLight.position);
    ShaderExtensions::SetUniform(*_shaderProgram.get(), "vu_lights[0].direction", uniforms.ShaderLight.GetDirection());
    ShaderExtensions::SetUniform(*_shaderProgram.get(), "vu_lights[0].viewProjectionMatrix", uniforms.ShaderLight.shadowMapProjectionMatrix * uniforms.ShaderLight.GetViewMatrix());

    ShaderExtensions::SetUniform(*_shaderProgram.get(), "fu_material.diffuseColour", uniforms.ShaderMaterial.diffuseColour);
    ShaderExtensions::SetUniform(*_shaderProgram.get(), "fu_material.isDiffuseTextureEnabled", isDiffuseTextureEnabled);
    ShaderExtensions::SetUniform(*_shaderProgram.get(), "fu_material.diffuseTextureSlot", 0);
    ShaderExtensions::SetUniform(*_shaderProgram.get(), "fu_material.specularColour", uniforms.ShaderMaterial.specularColour);
    ShaderExtensions::SetUniform(*_shaderProgram.get(), "fu_material.isSpecularTextureEnabled", isSpecularTextureEnabled);
    ShaderExtensions::SetUniform(*_shaderProgram.get(), "fu_material.specularTextureSlot", 1);
    ShaderExtensions::SetUniform(*_shaderProgram.get(), "fu_material.emissiveColour", uniforms.ShaderMaterial.emissiveColour);
    ShaderExtensions::SetUniform(*_shaderProgram.get(), "fu_material.isEmissiveTextureEnabled", isEmissiveTextureEnabled);
    ShaderExtensions::SetUniform(*_shaderProgram.get(), "fu_material.emissiveTextureSlot", 2);
    ShaderExtensions::SetUniform(*_shaderProgram.get(), "fu_material.shininess", uniforms.ShaderMaterial.shininess);

    ShaderExtensions::SetUniform(*_shaderProgram.get(), "fu_materialSceneProduct.sceneColour", uniforms.SceneAmbientColour);
    
    ShaderExtensions::SetUniform(*_shaderProgram.get(), "fu_lights[0].type", static_cast<int>(uniforms.ShaderLight.Type));
    ShaderExtensions::SetUniform(*_shaderProgram.get(), "fu_lights[0].isEnabled", uniforms.ShaderLight.isEnabled);
    ShaderExtensions::SetUniform(*_shaderProgram.get(), "fu_lights[0].position", uniforms.ShaderLight.position);
    ShaderExtensions::SetUniform(*_shaderProgram.get(), "fu_lights[0].direction", uniforms.ShaderLight.GetDirection());
    ShaderExtensions::SetUniform(*_shaderProgram.get(), "vu_lights[0].spotInnerCutoffCosine", MathsHelper::Cosine(MathsHelper::DegreesToRadians(uniforms.ShaderLight.spotInnerCutoffDegrees)));
    ShaderExtensions::SetUniform(*_shaderProgram.get(), "vu_lights[0].spotOuterCutoffCosine", MathsHelper::Cosine(MathsHelper::DegreesToRadians(uniforms.ShaderLight.spotOuterCutoffDegrees)));
    ShaderExtensions::SetUniform(*_shaderProgram.get(), "fu_lights[0].ambientColour", uniforms.ShaderLight.ambientColour);
    ShaderExtensions::SetUniform(*_shaderProgram.get(), "fu_lights[0].diffuseColour", uniforms.ShaderLight.diffuseColour);
    ShaderExtensions::SetUniform(*_shaderProgram.get(), "fu_lights[0].specularColour", uniforms.ShaderLight.specularColour);
    ShaderExtensions::SetUniform(*_shaderProgram.get(), "fu_lights[0].intensityMultiplier", uniforms.ShaderLight.intensityMultiplier);
    ShaderExtensions::SetUniform(*_shaderProgram.get(), "fu_lights[0].constantAttenuation", uniforms.ShaderLight.constantAttenuation);
    ShaderExtensions::SetUniform(*_shaderProgram.get(), "fu_lights[0].linearAttenuation", uniforms.ShaderLight.linearAttenuation);
    ShaderExtensions::SetUniform(*_shaderProgram.get(), "fu_lights[0].quadraticAttenuation", uniforms.ShaderLight.quadraticAttenuation);
    ShaderExtensions::SetUniform(*_shaderProgram.get(), "fu_lights[0].shadowMapTextureSlot", 3);

    mesh.Draw();
}
