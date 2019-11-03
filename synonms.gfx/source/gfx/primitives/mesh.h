#pragma once

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
                Mesh(const VertexDefinition& vertexDefinition, float* vertexData, unsigned int noOfVertices, unsigned int* indexData, unsigned int noOfIndices);
                void Draw();
                std::string ToString();

            private:
                unsigned int _indexBufferId{ 0 };
                unsigned int _noOfIndices{ 0 };
                unsigned int _noOfVertices{ 0 };
                unsigned int _vertexArrayId{ 0 };
                unsigned int _vertexBufferId{ 0 };
            };
        }
    }
}