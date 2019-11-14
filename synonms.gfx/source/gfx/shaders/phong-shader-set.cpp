#include "phong-shader-set.h"

using namespace synonms::gfx::environment;
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

    SetUniform("vu_isLightEnabled", uniforms.ShaderLight.IsEnabled);
    SetUniform("vu_lightPosition", uniforms.ShaderLight.GetPosition());

    SetUniform("fu_material.ambientColour", uniforms.ShaderMaterial.GetAmbientColour());
    SetUniform("fu_material.diffuseColour", uniforms.ShaderMaterial.GetDiffuseColour());
    SetUniform("fu_material.specularColour", uniforms.ShaderMaterial.GetSpecularColour());
    SetUniform("fu_material.emissiveColour", uniforms.ShaderMaterial.GetEmissiveColour());
    SetUniform("fu_material.opacity", uniforms.ShaderMaterial.GetOpacity());
    SetUniform("fu_material.shininess", uniforms.ShaderMaterial.GetShininess());

    SetUniform("fu_isTextureEnabled", false);
    SetUniform("fu_textureSlot", 0);

    SetUniform("fu_light.isEnabled", uniforms.ShaderLight.IsEnabled);
    SetUniform("fu_light.position", uniforms.ShaderLight.GetPosition());
    SetUniform("fu_light.ambientColour", uniforms.ShaderLight.ambientColour);
    SetUniform("fu_light.diffuseColour", uniforms.ShaderLight.diffuseColour);
    SetUniform("fu_light.specularColour", uniforms.ShaderLight.specularColour);
    SetUniform("fu_light.intensityMultiplier", uniforms.ShaderLight.IntensityMultiplier);
    SetUniform("fu_light.constantAttenuation", uniforms.ShaderLight.ConstantAttenuation);
    SetUniform("fu_light.linearAttenuation", uniforms.ShaderLight.LinearAttenuation);
    SetUniform("fu_light.quadraticAttenuation", uniforms.ShaderLight.QuadraticAttenuation);

    mesh.Draw();
}
