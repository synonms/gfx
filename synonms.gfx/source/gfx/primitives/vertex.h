#pragma once

#include <gfx\mathematics\linear\vector2.h>
#include <gfx\mathematics\linear\vector3.h>

namespace synonms
{
    namespace gfx
    {
        namespace primitives
        {
            class Vertex
            {
            public:
                Vertex(const mathematics::linear::Vector3<float>& position, 
                    const mathematics::linear::Vector3<float>& normal, 
                    const mathematics::linear::Vector2<float>& textureCoords)
                    : position(position)
                    , normal(normal)
                    , textureCoords(textureCoords)
                {
                }

                mathematics::linear::Vector3<float> position;
                mathematics::linear::Vector3<float> normal;
                mathematics::linear::Vector2<float> textureCoords;
            };
        }
    }
}