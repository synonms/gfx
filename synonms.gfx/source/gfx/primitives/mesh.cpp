#include "mesh.h"

#include <gfx\enumerators\data-type.h>

#include <opengl\state-manager.h>
#include <opengl\vertex-attribute-array.h>

#include <iostream>
#include <sstream>

using namespace synonms::gfx::api;
using namespace synonms::gfx::primitives;
using namespace synonms::gfx::enumerators;

Mesh::Mesh(const std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices)
    : _vertices(vertices)
    , _indices(indices)
{
    _vertexArray = std::make_unique<opengl::VertexArray>();
    _vertexArray->Bind();

    _vertexBuffer = std::make_unique<opengl::VertexBuffer>();
    _vertexBuffer->Bind();
    opengl::VertexBuffer::SendData(&_vertices[0], _vertices.size() * sizeof(Vertex), opengl::enumerators::DataUsage::StaticDraw);

    // Positions
    opengl::VertexAttributeArray::Enable(0);
    opengl::VertexAttributeArray::Configure(0, 3, opengl::enumerators::DataType::Float, sizeof(Vertex), false, 0);

    // Normals
    opengl::VertexAttributeArray::Enable(1);
    opengl::VertexAttributeArray::Configure(1, 3, opengl::enumerators::DataType::Float, sizeof(Vertex), false, offsetof(Vertex, normal));

    // Tex Coords
    opengl::VertexAttributeArray::Enable(2);
    opengl::VertexAttributeArray::Configure(2, 2, opengl::enumerators::DataType::Float, sizeof(Vertex), false, offsetof(Vertex, textureCoords));


    _indexBuffer = std::make_unique<opengl::IndexBuffer>();
    _indexBuffer->Bind();
    opengl::IndexBuffer::SendData(&_indices[0], _indices.size() * sizeof(unsigned int), opengl::enumerators::DataUsage::StaticDraw);
}

Mesh::Mesh(Mesh&& other) noexcept
    : _vertices(std::exchange(other._vertices, {}))
    , _indices(std::exchange(other._indices, {}))
    , _indexBuffer(std::exchange(other._indexBuffer, nullptr))
    , _vertexArray(std::exchange(other._vertexArray, nullptr))
    , _vertexBuffer(std::exchange(other._vertexBuffer, nullptr))
    , _isBackFaceCulled(std::exchange(other._isBackFaceCulled, false))
{
}

Mesh& Mesh::operator=(Mesh&& other) noexcept
{
    _vertices = std::exchange(other._vertices, {});
    _indices = std::exchange(other._indices, {});
    _indexBuffer = std::exchange(other._indexBuffer, nullptr);
    _vertexArray = std::exchange(other._vertexArray, nullptr);
    _vertexBuffer = std::exchange(other._vertexBuffer, nullptr);
    _isBackFaceCulled = std::exchange(other._isBackFaceCulled, false);
        
    return *this;
}

Mesh::~Mesh()
{
}

void Mesh::Draw() const
{
    opengl::StateManager::SetFaceCulling(_isBackFaceCulled);

    _vertexArray->Bind();

    _indexBuffer->Bind();
    opengl::IndexBuffer::Draw(opengl::enumerators::DrawMode::Triangles, _indices.size(), opengl::enumerators::DataType::UnsignedInt);
}

std::string Mesh::ToString() const
{
    std::stringstream stream;
    stream << "[Mesh: VertexArrayId " << _vertexArray->GetVertexArrayId() << ", VertexBufferId " << _vertexBuffer->GetVertexBufferId() << ", IndexBufferId " << _indexBuffer->GetIndexBufferId() << ", " << _vertices.size() << " vertices, " << _indices.size() << " indices]";

    return stream.str();
}