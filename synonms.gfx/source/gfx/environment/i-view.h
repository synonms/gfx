#pragma once

#include <memory>

#include <gfx\mathematics\linear\matrix4x4.h>

namespace synonms
{
    namespace gfx
    {
        namespace environment
        {
            class IView
            {
            public:
                virtual const mathematics::linear::Matrix4x4& GetProjectionMatrix() const = 0;
            };
        }
    }
}
