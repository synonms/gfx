#pragma once

#include <gfx\shaders\shadowmap-shader-uniforms.h>
#include <gfx\shaders\shader-set.h>
#include <gfx\primitives\mesh.h>

namespace synonms
{
    namespace gfx
    {
        namespace shaders
        {

            class ShadowmapShaderSet : public ShaderSet
            {
            public:
                ShadowmapShaderSet(const std::string& vertexShaderSource, const std::string& fragmentShaderSource);

                void Render(const ShadowmapShaderUniforms& uniforms, const primitives::Mesh& mesh);
            };
        }
    }
}