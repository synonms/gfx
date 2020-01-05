#pragma once

#include <gfx/primitives/mesh.h>

#include <memory>

namespace synonms
{
    namespace gfx
    {
        namespace primitives
        {
            class PrimitiveFactory
            {
            public:
                static std::shared_ptr<Mesh> CreateBox(float width, float height, float depth);
                static std::shared_ptr<Mesh> CreatePlane(float width, float height);
                static std::shared_ptr<Mesh> CreatePlane(float left, float bottom, float width, float height);
            };
        }
    }
}