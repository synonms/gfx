#pragma once

#include <gfx\mathematics\linear\matrix4x4.h>
#include <gfx\mathematics\linear\transform.h>
#include <gfx\mathematics\linear\vector3.h>

namespace synonms
{
    namespace gfx
    {
        namespace environment
        {
            class Camera
            {
            public:
                inline mathematics::linear::Matrix4x4 GetViewMatrix() const { return mathematics::linear::Matrix4x4::CreateViewFrom(position, rotationDegrees, false); }

                mathematics::linear::Vector3<float> position{ 0.0f, 0.0f, 0.0f };
                mathematics::linear::Vector3<float> rotationDegrees{ 0.0f, 0.0f, 0.0f };
            };
        }
    }
}
