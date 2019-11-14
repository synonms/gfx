#pragma once

#include <gfx\shaders\phong-shader-uniforms.h>
#include <gfx\shaders\shader-set.h>
#include <gfx\primitives\mesh.h>

namespace synonms
{
    namespace gfx
    {
        namespace shaders
        {
            
            class PhongShaderSet : public ShaderSet
            {
            public:
                PhongShaderSet(const std::string& vertexShaderSource, const std::string& fragmentShaderSource);

                void Render(const PhongShaderUniforms& uniforms, const primitives::Mesh& mesh);
            };
        }
    }
}