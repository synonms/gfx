#pragma once

#include <gfx\geometry\vector2.h>
#include <gfx\geometry\vector3.h>

namespace synonms
{
    namespace gfx
    {
        namespace primitives
        {
            class Vertex
            {
            public:
                Vertex(const geometry::Vector3<float>& position, 
                    const geometry::Vector3<float>& normal, 
                    const geometry::Vector2<float>& textureCoords,
                    const geometry::Vector3<float>& tangent)
                    : position(position)
                    , normal(normal)
                    , textureCoords(textureCoords)
                    , tangent(tangent)
                {
                }

                geometry::Vector3<float> position;
                geometry::Vector3<float> normal;
                geometry::Vector2<float> textureCoords;
                geometry::Vector3<float> tangent;
            };
        }
    }
}