#pragma once

#include <gfx\environment\light.h>
#include <gfx\materials\material.h>
#include <gfx\mathematics\linear\matrix4x4.h>
#include <gfx\mathematics\linear\vector4.h>

namespace synonms
{
    namespace gfx
    {
        namespace shaders
        {
            class PhongShaderUniforms
            {
            public:
                PhongShaderUniforms(const mathematics::linear::Matrix4x4& projectionMatrix,
                    const mathematics::linear::Matrix4x4& viewMatrix,
                    const mathematics::linear::Matrix4x4& modelMatrix,
                    const mathematics::linear::Matrix3x3& normalMatrix,
                    const materials::Material& material,
                    const environment::Light& light,
                    const mathematics::linear::Vector4<float>& sceneAmbientColour)
                    : ProjectionMatrix(projectionMatrix)
                    , ViewMatrix(viewMatrix)
                    , ModelMatrix(modelMatrix)
                    , NormalMatrix(normalMatrix)
                    , ShaderMaterial(material)
                    , ShaderLight(light)
                    , SceneAmbientColour(sceneAmbientColour)
                {}

                const mathematics::linear::Matrix4x4& ProjectionMatrix;
                const mathematics::linear::Matrix4x4& ViewMatrix;
                const mathematics::linear::Matrix4x4& ModelMatrix;
                const mathematics::linear::Matrix3x3& NormalMatrix;
                const materials::Material& ShaderMaterial;
                const environment::Light& ShaderLight;
                mathematics::linear::Vector4<float> SceneAmbientColour;
            };
        }
    }
}