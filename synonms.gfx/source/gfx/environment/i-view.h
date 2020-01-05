#pragma once

#include <memory>

#include <gfx\transforms\matrix4x4.h>

namespace synonms
{
    namespace gfx
    {
        namespace environment
        {
            class IView
            {
            public:
                virtual const transforms::Matrix4x4& GetProjectionMatrix() const = 0;
            };
        }
    }
}
