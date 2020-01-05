#pragma once

#include <gfx\materials\pbr-material.h>
#include <gfx\transforms\matrix3x3.h>
#include <gfx\transforms\matrix4x4.h>

namespace synonms
{
    namespace gfx
    {
        namespace shaders
        {
            class DeferredGBufferShaderUniforms
            {
            public:
                DeferredGBufferShaderUniforms(const transforms::Matrix4x4& projectionMatrix,
                    const transforms::Matrix4x4& viewMatrix,
                    const transforms::Matrix4x4& modelMatrix,
                    const transforms::Matrix3x3& normalMatrix,
                    const materials::PBRMaterial& material)
                    : ProjectionMatrix(projectionMatrix)
                    , ViewMatrix(viewMatrix)
                    , ModelMatrix(modelMatrix)
                    , NormalMatrix(normalMatrix)
                    , ShaderMaterial(material)
                {}

                const transforms::Matrix4x4& ProjectionMatrix;
                const transforms::Matrix4x4& ViewMatrix;
                const transforms::Matrix4x4& ModelMatrix;
                const transforms::Matrix3x3& NormalMatrix;
                const materials::PBRMaterial& ShaderMaterial;
            };
        }
    }
}