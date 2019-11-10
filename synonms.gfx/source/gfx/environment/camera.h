#pragma once

#include <memory>

#include <gfx\mathematics\linear\matrix4x4.h>
#include <gfx\mathematics\linear\transform.h>

namespace synonms
{
    namespace gfx
    {
        namespace environment
        {
            class Camera
            {
            public:
                mathematics::linear::Transform& GetTransform() { return _transform; }

            private:
                mathematics::linear::Transform _transform{};
            };
        }
    }
}
