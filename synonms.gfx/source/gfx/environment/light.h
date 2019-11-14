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

                mathematics::linear::Vector3<float> ambientColour{0.2f, 0.2f, 0.2f};
                mathematics::linear::Vector3<float> diffuseColour{0.5f, 0.5f, 0.5f};
                mathematics::linear::Vector3<float> specularColour{1.0f, 1.0f, 1.0f};

                bool IsEnabled{ true };
                float IntensityMultiplier{1.0f};
                float ConstantAttenuation{1.0f};
                float LinearAttenuation{0.0f};
                float QuadraticAttenuation{0.0f};

                inline const mathematics::linear::Vector3<float>& GetPosition() const { return _transform.position; }
                inline float* GetPositionData() { return &_transform.position.x; }
                inline const mathematics::linear::Vector3<float>& GetRotation() const { return _transform.rotationDegrees; }
                inline float* GetRotationData() { return &_transform.rotationDegrees.x; }

                inline void SetPosition(const mathematics::linear::Vector3<float>& position) { _transform.position = position; }
                inline void SetRotation(const mathematics::linear::Vector3<float>& rotationDegrees) { _transform.rotationDegrees = rotationDegrees; }

            private:
                mathematics::linear::Transform _transform{};
            };
        }
    }
}