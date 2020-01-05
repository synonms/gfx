#pragma once

#include <gfx\environment\camera.h>
#include <gfx\environment\light.h>
#include <gfx\primitives\mesh-instance.h>
#include <gfx\transforms\matrix3x3.h>
#include <gfx\transforms\matrix4x4.h>
#include <gfx\geometry\vector4.h>

namespace synonms
{
    namespace gfx
    {
        namespace shaders
        {
            class PBRShaderData
            {
            public:
                PBRShaderData(const transforms::Matrix4x4& projectionMatrix,
                    const transforms::Matrix4x4& viewMatrix,
                    const primitives::MeshInstance& meshInstance,
                    const environment::Camera& camera,
                    const environment::Light& light)
                    : projectionMatrix(projectionMatrix)
                    , viewMatrix(viewMatrix)
                    , meshInstance(meshInstance)
                    , camera(camera)
                    , light(light)
                {}

                const transforms::Matrix4x4& projectionMatrix;
                const transforms::Matrix4x4& viewMatrix;
                const primitives::MeshInstance& meshInstance;
                const environment::Camera& camera;
                const environment::Light& light;
            };
        }
    }
}
