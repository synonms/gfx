#pragma once

#include <gfx\primitives\vertex.h>

#include <string>
#include <vector>

namespace synonms
{
    namespace gfx
    {
        namespace primitives
        {
            class Mesh
            {
            public:
                Mesh(const std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices);
                void Draw() const;
                std::string ToString() const;

            private:
                std::vector<Vertex> _vertices;
                std::vector<unsigned int> _indices;

                unsigned int _indexBufferId{ 0 };
                unsigned int _vertexArrayId{ 0 };
                unsigned int _vertexBufferId{ 0 };
                bool _isBackFaceCulled{ true };
            };
        }
    }
}