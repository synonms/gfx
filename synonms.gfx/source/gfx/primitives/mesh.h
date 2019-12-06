#pragma once

#include <gfx\primitives\vertex.h>

#include <opengl\index-buffer.h>
#include <opengl\vertex-array.h>
#include <opengl\vertex-buffer.h>

#include <memory>
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
                Mesh(Mesh&& other) noexcept;
                Mesh& operator=(Mesh&& other) noexcept;
                ~Mesh();

                Mesh() = delete;
                Mesh(const Mesh& other) = delete;
                Mesh& operator=(const Mesh& other) = delete;

                void Draw() const;
                std::string ToString() const;

            private:
                std::vector<Vertex> _vertices;
                std::vector<unsigned int> _indices;

                std::unique_ptr<api::opengl::IndexBuffer> _indexBuffer{ nullptr };
                std::unique_ptr<api::opengl::VertexArray> _vertexArray{ nullptr };
                std::unique_ptr<api::opengl::VertexBuffer> _vertexBuffer{ nullptr };
                bool _isBackFaceCulled{ true };
            };
        }
    }
}