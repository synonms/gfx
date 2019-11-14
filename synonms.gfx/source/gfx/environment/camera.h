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
                inline mathematics::linear::Matrix4x4 GetViewMatrix() const { return _transform.GetViewMatrix(); }
                inline void SetPosition(const mathematics::linear::Vector3<float>& position) { _transform.position = position; }
                inline void SetRotation(const mathematics::linear::Vector3<float>& rotationDegrees) { _transform.rotationDegrees = rotationDegrees; }

            private:
                mathematics::linear::Transform _transform{};
            };
        }
    }
}
