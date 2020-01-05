#pragma once

#include <gfx\environment\light.h>
#include <gfx\materials\material.h>
#include <gfx\transforms\matrix3x3.h>
#include <gfx\transforms\matrix4x4.h>
#include <gfx\geometry\vector4.h>

namespace synonms
{
    namespace gfx
    {
        namespace shaders
        {
            class PhongShaderUniforms
            {
            public:
                PhongShaderUniforms(const transforms::Matrix4x4& projectionMatrix,
                    const transforms::Matrix4x4& viewMatrix,
                    const transforms::Matrix4x4& modelMatrix,
                    const transforms::Matrix3x3& normalMatrix,
                    const materials::Material& material,
                    const environment::Light& light,
                    const geometry::Vector4<float>& sceneAmbientColour)
                    : ProjectionMatrix(projectionMatrix)
                    , ViewMatrix(viewMatrix)
                    , ModelMatrix(modelMatrix)
                    , NormalMatrix(normalMatrix)
                    , ShaderMaterial(material)
                    , ShaderLight(light)
                    , SceneAmbientColour(sceneAmbientColour)
                {}

                const transforms::Matrix4x4& ProjectionMatrix;
                const transforms::Matrix4x4& ViewMatrix;
                const transforms::Matrix4x4& ModelMatrix;
                const transforms::Matrix3x3& NormalMatrix;
                const materials::Material& ShaderMaterial;
                const environment::Light& ShaderLight;
                geometry::Vector4<float> SceneAmbientColour;
            };
        }
    }
}