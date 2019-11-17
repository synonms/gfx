#include "phong-shader-set.h"

#include <gfx\mathematics\maths-helper.h>

using namespace synonms::gfx::environment;
using namespace synonms::gfx::materials;
using namespace synonms::gfx::mathematics;
using namespace synonms::gfx::mathematics::linear;
using namespace synonms::gfx::primitives;
using namespace synonms::gfx::shaders;

PhongShaderSet::PhongShaderSet(const std::string& vertexShaderSource, const std::string& fragmentShaderSource)
    : ShaderSet(vertexShaderSource, fragmentShaderSource)
{}

void PhongShaderSet::Render(const PhongShaderUniforms& uniforms, const Mesh& mesh)
{
    Use();

    SetUniform("vu_modelMatrix", uniforms.ModelMatrix);
    SetUniform("vu_viewMatrix", uniforms.ViewMatrix);
    SetUniform("vu_projectionMatrix", uniforms.ProjectionMatrix);
    SetUniform("vu_normalMatrix", uniforms.NormalMatrix);

    SetUniform("vu_lights[0].type", static_cast<int>(uniforms.ShaderLight.Type));
    SetUniform("vu_lights[0].isEnabled", uniforms.ShaderLight.isEnabled);
    SetUniform("vu_lights[0].position", uniforms.ShaderLight.position);
    SetUniform("vu_lights[0].direction", uniforms.ShaderLight.direction);

    SetUniform("fu_material.diffuseColour", uniforms.ShaderMaterial.diffuseColour);
    SetUniform("fu_material.isDiffuseTextureEnabled", uniforms.ShaderMaterial.IsTextureEnabled(Material::TextureSlot::Diffuse));
    SetUniform("fu_material.diffuseTextureSlot", static_cast<int>(Material::TextureSlot::Diffuse));
    SetUniform("fu_material.specularColour", uniforms.ShaderMaterial.specularColour);
    SetUniform("fu_material.isSpecularTextureEnabled", uniforms.ShaderMaterial.IsTextureEnabled(Material::TextureSlot::Specular));
    SetUniform("fu_material.specularTextureSlot", static_cast<int>(Material::TextureSlot::Specular));
    SetUniform("fu_material.emissiveColour", uniforms.ShaderMaterial.emissiveColour);
    SetUniform("fu_material.isEmissiveTextureEnabled", uniforms.ShaderMaterial.IsTextureEnabled(Material::TextureSlot::Emissive));
    SetUniform("fu_material.emissiveTextureSlot", static_cast<int>(Material::TextureSlot::Emissive));
    SetUniform("fu_material.shininess", uniforms.ShaderMaterial.shininess);

    SetUniform("fu_materialSceneProduct.sceneColour", uniforms.SceneAmbientColour);
    
    SetUniform("fu_lights[0].type", static_cast<int>(uniforms.ShaderLight.Type));
    SetUniform("fu_lights[0].isEnabled", uniforms.ShaderLight.isEnabled);
    SetUniform("fu_lights[0].position", uniforms.ShaderLight.position);
    SetUniform("fu_lights[0].direction", uniforms.ShaderLight.direction);
    SetUniform("vu_lights[0].spotInnerCutoffCosine", MathsHelper::Cosine(MathsHelper::DegreesToRadians(uniforms.ShaderLight.spotInnerCutoffDegrees)));
    SetUniform("vu_lights[0].spotOuterCutoffCosine", MathsHelper::Cosine(MathsHelper::DegreesToRadians(uniforms.ShaderLight.spotOuterCutoffDegrees)));
    SetUniform("fu_lights[0].ambientColour", uniforms.ShaderLight.ambientColour);
    SetUniform("fu_lights[0].diffuseColour", uniforms.ShaderLight.diffuseColour);
    SetUniform("fu_lights[0].specularColour", uniforms.ShaderLight.specularColour);
    SetUniform("fu_lights[0].intensityMultiplier", uniforms.ShaderLight.intensityMultiplier);
    SetUniform("fu_lights[0].constantAttenuation", uniforms.ShaderLight.constantAttenuation);
    SetUniform("fu_lights[0].linearAttenuation", uniforms.ShaderLight.linearAttenuation);
    SetUniform("fu_lights[0].quadraticAttenuation", uniforms.ShaderLight.quadraticAttenuation);

    mesh.Draw();
}
