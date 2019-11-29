#pragma once

#include <gfx\mathematics\linear\matrix4x4.h>

namespace synonms
{
    namespace gfx
    {
        namespace shaders
        {
            class ShadowmapShaderUniforms
            {
            public:
                ShadowmapShaderUniforms(const mathematics::linear::Matrix4x4& modelViewProjectionMatrix)
                    : ModelViewProjectionMatrix(modelViewProjectionMatrix)
                {}

                const mathematics::linear::Matrix4x4& ModelViewProjectionMatrix;
            };
        }
    }
}