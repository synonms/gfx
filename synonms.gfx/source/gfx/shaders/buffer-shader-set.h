#pragma once

#include <gfx\shaders\shader-set.h>
#include <gfx\primitives\mesh.h>

namespace synonms
{
    namespace gfx
    {
        namespace shaders
        {
            class BufferShaderSet : public ShaderSet
            {
            public:
                BufferShaderSet(const std::string& vertexShaderSource, const std::string& fragmentShaderSource);

                void Render(int textureSlot, const primitives::Mesh& mesh);
            };
        }
    }
}