#pragma once

#include <gfx\mathematics\linear\matrix4x4.h>
#include <gfx\mathematics\linear\vector4.h>
#include <gfx\mathematics\linear\vector3.h>

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

                mathematics::linear::Vector3<float> position{ 0.0f, 0.0f, 0.0f };
                mathematics::linear::Vector3<float> target{ 0.0f, 0.0f, 0.0f };

                mathematics::linear::Vector4<float> ambientColour{0.005f, 0.005f, 0.005f, 1.0f};
                mathematics::linear::Vector4<float> diffuseColour{1.0f, 1.0f, 1.0f, 1.0f};
                mathematics::linear::Vector4<float> specularColour{0.1f, 0.1f, 0.1f, 1.0f};

                mathematics::linear::Matrix4x4 shadowMapProjectionMatrix{}; // Ortho for directional, Perspective for positional
                std::shared_ptr<api::opengl::Texture> shadowMapDepthTexture{ nullptr };

                bool isEnabled{ true };
                float spotInnerCutoffDegrees{ 30.0f };
                float spotOuterCutoffDegrees{ 60.0f };
                float intensityMultiplier{1.0f};
                float constantAttenuation{1.0f};
                float linearAttenuation{0.1f};
                float quadraticAttenuation{0.01f};

                inline mathematics::linear::Vector3<float> GetDirection() const {
                    return Type == LightType::Positional ? target - position : mathematics::linear::Vector3<float>(0.0f, -1.0f, 0.0f);
                }

                inline mathematics::linear::Matrix4x4 GetViewMatrix() const { 
                    return mathematics::linear::Matrix4x4::CreateViewFrom(position, target);
                }
            };
        }
    }
}