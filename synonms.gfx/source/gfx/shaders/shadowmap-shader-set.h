#pragma once

#include <gfx\mathematics\linear\matrix4x4.h>
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

                void Render(const mathematics::linear::Matrix4x4& modelViewProjectionMatrix, const primitives::Mesh& mesh);
            };
        }
    }
}