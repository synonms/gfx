#pragma once

#include <gfx\transforms\matrix4x4.h>
#include <gfx\geometry\point3.h>
#include <gfx\geometry\vector3.h>
#include <gfx\geometry\vector4.h>

#include <opengl\texture.h>

#include <memory>

namespace synonms
{
    namespace gfx 
    {
        namespace environment
        {
            class Light
            {
            public:
                enum class LightType
                {
                    Directional = 0,
                    Positional = 1,
                    Spot = 2
                };

            public:
                Light(LightType type = LightType::Positional) 
                    : Type(type) 
                {}

                LightType Type;

                geometry::Point3<float> position{ 0.0f, 0.0f, 0.0f };
                geometry::Point3<float> target{ 0.0f, 0.0f, 0.0f };

                geometry::Vector3<float> radiance{ 1.0f, 1.0f, 1.0f };

                geometry::Vector4<float> ambientColour{0.005f, 0.005f, 0.005f, 1.0f};
                geometry::Vector4<float> diffuseColour{1.0f, 1.0f, 1.0f, 1.0f};
                geometry::Vector4<float> specularColour{0.1f, 0.1f, 0.1f, 1.0f};

                transforms::Matrix4x4 shadowMapProjectionMatrix{}; // Ortho for directional, Perspective for positional
                std::shared_ptr<api::opengl::Texture> shadowMapDepthTexture{ nullptr };

                bool isEnabled{ true };
                float spotInnerCutoffDegrees{ 30.0f };
                float spotOuterCutoffDegrees{ 60.0f };
                float intensityMultiplier{1.0f};
                float constantAttenuation{1.0f};
                float linearAttenuation{0.1f};
                float quadraticAttenuation{0.01f};

                inline geometry::Vector3<float> GetDirection() const {
                    auto direction = position.VectorTo(target);
                    direction.Normalise();

                    return direction;
                }

                inline transforms::Matrix4x4 GetViewMatrix() const {
                    return transforms::Matrix4x4::CreateViewFrom(position, target);
                }
            };
        }
    }
}