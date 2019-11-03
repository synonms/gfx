#pragma once

#include <memory>

#include <gfx\mathematics\linear\matrix4x4.h>

namespace synonms
{
    namespace gfx
    {
        namespace environment
        {
            class Camera
            {
            public:
                mathematics::linear::Matrix4x4<float> GetViewMatrix();
            };
        }
    }
}
