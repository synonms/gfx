#pragma once

#include <gfx\mathematics\linear\transform.h>
#include <gfx\mathematics\linear\vector3.h>

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
                mathematics::linear::Vector3<float> direction{ 0.0f, 0.0f, 1.0f };

                mathematics::linear::Vector4<float> ambientColour{0.005f, 0.005f, 0.005f, 1.0f};
                mathematics::linear::Vector4<float> diffuseColour{1.0f, 1.0f, 1.0f, 1.0f};
                mathematics::linear::Vector4<float> specularColour{0.1f, 0.1f, 0.1f, 1.0f};

                bool isEnabled{ true };
                float spotInnerCutoffDegrees{ 30.0f };
                float spotOuterCutoffDegrees{ 60.0f };
                float intensityMultiplier{1.0f};
                float constantAttenuation{1.0f};
                float linearAttenuation{0.1f};
                float quadraticAttenuation{0.01f};
            };
        }
    }
}