#pragma once

#include <gfx/primitives/mesh.h>

namespace synonms
{
    namespace gfx
    {
        namespace primitives
        {
            class PrimitiveFactory
            {
            public:
                static Mesh CreateBox(float width, float height, float depth);
                static Mesh CreatePlane(float width, float height);
            };
        }
    }
}