#include "deferred-lighting-shader.h"

#include <gfx\mathematics\maths-helper.h>
#include <gfx\shaders\shader-extensions.h>

#include <opengl\factories\shader-factory.h>
#include <opengl\texture.h>

using namespace synonms::gfx::mathematics;
using namespace synonms::gfx::primitives;
using namespace synonms::gfx::shaders;

using namespace synonms::gfx::api;

DeferredLightingShader::DeferredLightingShader(const std::string& vertexShaderSource, const std::string& fragmentShaderSource)
{
    _shaderProgram = opengl::factories::ShaderFactory::Create(vertexShaderSource, fragmentShaderSource);
}

void DeferredLightingShader::Render(const DeferredLightingShaderUniforms& data, const Mesh& mesh)
{
    _shaderProgram->Use();

    auto uniforms = _shaderProgram->GetActiveUniforms();

    ShaderExtensions::SetUniform(*_shaderProgram.get(), "fu_viewPosition", data.ViewPosition);

    opengl::Texture::ActivateSlot(0);
    data.PositionTexture.Bind();
    ShaderExtensions::SetUniform(*_shaderProgram.get(), "fu_positionTextureSlot", 0);

    opengl::Texture::ActivateSlot(1);
    data.NormalTexture.Bind();
    ShaderExtensions::SetUniform(*_shaderProgram.get(), "fu_normalTextureSlot", 1);

    opengl::Texture::ActivateSlot(2);
    data.AlbedoSpecTexture.Bind();
    ShaderExtensions::SetUniform(*_shaderProgram.get(), "fu_albedoSpecTextureSlot", 2);

    ShaderExtensions::SetUniform(*_shaderProgram.get(), "fu_lights[0].type", static_cast<int>(data.ShaderLight.Type));
    ShaderExtensions::SetUniform(*_shaderProgram.get(), "fu_lights[0].isEnabled", data.ShaderLight.isEnabled);
    ShaderExtensions::SetUniform(*_shaderProgram.get(), "fu_lights[0].position", data.ShaderLight.position);
    ShaderExtensions::SetUniform(*_shaderProgram.get(), "fu_lights[0].direction", data.ShaderLight.GetDirection());
    ShaderExtensions::SetUniform(*_shaderProgram.get(), "fu_lights[0].viewProjectionMatrix", data.ShaderLight.shadowMapProjectionMatrix * data.ShaderLight.GetViewMatrix());

    ShaderExtensions::SetUniform(*_shaderProgram.get(), "fu_lights[0].spotInnerCutoffCosine", MathsHelper::Cosine(MathsHelper::DegreesToRadians(data.ShaderLight.spotInnerCutoffDegrees)));
    ShaderExtensions::SetUniform(*_shaderProgram.get(), "fu_lights[0].spotOuterCutoffCosine", MathsHelper::Cosine(MathsHelper::DegreesToRadians(data.ShaderLight.spotOuterCutoffDegrees)));
    ShaderExtensions::SetUniform(*_shaderProgram.get(), "fu_lights[0].ambientColour", data.ShaderLight.ambientColour);
    ShaderExtensions::SetUniform(*_shaderProgram.get(), "fu_lights[0].diffuseColour", data.ShaderLight.diffuseColour);
    ShaderExtensions::SetUniform(*_shaderProgram.get(), "fu_lights[0].specularColour", data.ShaderLight.specularColour);
    ShaderExtensions::SetUniform(*_shaderProgram.get(), "fu_lights[0].intensityMultiplier", data.ShaderLight.intensityMultiplier);
    ShaderExtensions::SetUniform(*_shaderProgram.get(), "fu_lights[0].constantAttenuation", data.ShaderLight.constantAttenuation);
    ShaderExtensions::SetUniform(*_shaderProgram.get(), "fu_lights[0].linearAttenuation", data.ShaderLight.linearAttenuation);
    ShaderExtensions::SetUniform(*_shaderProgram.get(), "fu_lights[0].quadraticAttenuation", data.ShaderLight.quadraticAttenuation);
    ShaderExtensions::SetUniform(*_shaderProgram.get(), "fu_lights[0].shadowMapTextureSlot", 3);

    mesh.Draw();
}
