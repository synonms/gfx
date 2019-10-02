#pragma once

#include <gfx\exports.h>

#include <gfx\primitives\vertex-attribute.h>
#include <gfx\primitives\vertex-definition.h>

#include <string>

namespace synonms
{
    namespace gfx
    {
        namespace primitives
        {
            class Mesh
            {
            public:
                SYNONMS_GFX_API Mesh(const VertexDefinition& vertexDefinition, float* vertexData, unsigned int noOfVertexBytes, unsigned int* indexData, unsigned int noOfIndexBytes);
                SYNONMS_GFX_API void Draw();
                SYNONMS_GFX_API std::string ToString();

            private:
                unsigned int _indexBufferId{ 0 };
                unsigned int _noOfIndexBytes{ 0 };
                unsigned int _noOfVertexBytes{ 0 };
                unsigned int _vertexArrayId{ 0 };
                unsigned int _vertexBufferId{ 0 };
            };
        }
    }
}