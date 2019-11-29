#include "shadowmap-shader-set.h"

using namespace synonms::gfx::primitives;
using namespace synonms::gfx::shaders;

ShadowmapShaderSet::ShadowmapShaderSet(const std::string& vertexShaderSource, const std::string& fragmentShaderSource)
    : ShaderSet(vertexShaderSource, fragmentShaderSource)
{}

void ShadowmapShaderSet::Render(const ShadowmapShaderUniforms& uniforms, const Mesh& mesh)
{
    Use();

    SetUniform("vu_modelViewProjectionMatrix", uniforms.ModelViewProjectionMatrix);

    mesh.Draw();
}
