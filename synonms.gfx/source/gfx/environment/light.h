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
                    Positional,
                    Spot
                };

            public:
                Light(LightType type = LightType::Positional) 
                    : Type(type) 
                {}

                LightType Type;

                mathematics::linear::Transform WorldTransform{};
                mathematics::linear::Vector3<float> DiffuseColour{1.0f, 1.0f, 1.0f};
                mathematics::linear::Vector3<float> SpecularColour{1.0f, 1.0f, 1.0f};
                mathematics::linear::Vector3<float> AmbientColour{1.0f, 1.0f, 1.0f};

                bool IsEnabled{ true };
                float AmbientIntensityMultiplier{ 0.2f };
                float IntensityMultiplier{1.0f};
                float ConstantAttenuation{1.0f};
                float LinearAttenuation{0.0f};
                float QuadraticAttenuation{0.0f};
            };
        }
    }
}