#pragma once

#include <gfx/environment/light.h>
#include <gfx\geometry\point3.h>

#include <opengl\texture.h>

namespace synonms
{
    namespace gfx
    {
        namespace shaders
        {
            class DeferredLightingShaderUniforms
            {
            public:
                DeferredLightingShaderUniforms(const geometry::Point3<float>& viewPosition,
                    const api::opengl::Texture& positionTexture,
                    const api::opengl::Texture& normalTexture,
                    const api::opengl::Texture& albedoSpecTexture,
                    const environment::Light& light)
                    : ViewPosition(viewPosition)
                    , PositionTexture(positionTexture)
                    , NormalTexture(normalTexture)
                    , AlbedoSpecTexture(albedoSpecTexture)
                    , ShaderLight(light)
                {}

                const geometry::Point3<float>& ViewPosition;
                const api::opengl::Texture& PositionTexture;
                const api::opengl::Texture& NormalTexture;
                const api::opengl::Texture& AlbedoSpecTexture;
                const environment::Light& ShaderLight;
            };
        }
    }
}