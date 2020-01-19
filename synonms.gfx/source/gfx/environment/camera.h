#pragma once

#include <gfx\transforms\matrix4x4.h>
#include <gfx\geometry\point3.h>
#include <gfx\geometry\vector3.h>

namespace synonms
{
    namespace gfx
    {
        namespace environment
        {
            class Camera
            {
            public:
                inline transforms::Matrix4x4 GetViewMatrix() const { return transforms::Matrix4x4::CreateViewFrom(position, rotationDegrees, false); }
                inline transforms::Matrix4x4 GetSceneRotationMatrix() const { return transforms::Matrix4x4::CreateViewFrom(geometry::Point3<float>(), rotationDegrees, true); }

                geometry::Point3<float> position{ 0.0f, 0.0f, 0.0f };
                geometry::Vector3<float> rotationDegrees{ 0.0f, 0.0f, 0.0f };
            };
        }
    }
}
