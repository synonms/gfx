#include "mesh.h"

#include <gfx\enumerators\data-type.h>

#include <glproxy\index-buffer.h>
#include <glproxy\system.h>
#include <glproxy\vertex-array.h>
#include <glproxy\vertex-attribute-array.h>
#include <glproxy\vertex-buffer.h>

#include <iostream>
#include <sstream>

using namespace synonms::gfx::primitives;
using namespace synonms::gfx::enumerators;

Mesh::Mesh(const std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices)
    : _vertices(vertices)
    , _indices(indices)
{
    _vertexArrayId = proxies::opengl::VertexArray::Generate(true);
    proxies::opengl::VertexArray::Bind(_vertexArrayId, true);

    _vertexBufferId = proxies::opengl::VertexBuffer::Generate(true);
    proxies::opengl::VertexBuffer::Bind(_vertexBufferId, true);
    proxies::opengl::VertexBuffer::SendData(&_vertices[0], _vertices.size() * sizeof(Vertex), proxies::opengl::enumerators::DataUsage::StaticDraw, true);

    // Positions
    proxies::opengl::VertexAttributeArray::Enable(0, true);
    proxies::opengl::VertexAttributeArray::Configure(0, 3, proxies::opengl::enumerators::DataType::Float, sizeof(Vertex), false, 0, true);

    // Normals
    proxies::opengl::VertexAttributeArray::Enable(1, true);
    proxies::opengl::VertexAttributeArray::Configure(1, 3, proxies::opengl::enumerators::DataType::Float, sizeof(Vertex), false, offsetof(Vertex, normal), true);

    // Tex Coords
    proxies::opengl::VertexAttributeArray::Enable(2, true);
    proxies::opengl::VertexAttributeArray::Configure(2, 2, proxies::opengl::enumerators::DataType::Float, sizeof(Vertex), false, offsetof(Vertex, textureCoords), true);


    _indexBufferId = proxies::opengl::IndexBuffer::Generate(true);
    proxies::opengl::IndexBuffer::Bind(_indexBufferId, true);
    proxies::opengl::IndexBuffer::SendData(&_indices[0], _indices.size() * sizeof(unsigned int), proxies::opengl::enumerators::DataUsage::StaticDraw, true);
}

void Mesh::Draw() const
{
    proxies::opengl::System::SetFaceCulling(_isBackFaceCulled);

    proxies::opengl::VertexArray::Bind(_vertexArrayId, true);

    proxies::opengl::IndexBuffer::Bind(_indexBufferId, true);
    proxies::opengl::IndexBuffer::Draw(proxies::opengl::enumerators::DrawMode::Triangles, _indices.size(), proxies::opengl::enumerators::DataType::UnsignedInt, true);
}

std::string Mesh::ToString() const
{
    std::stringstream stream;
    stream << "[Mesh: VertexArrayId " << _vertexArrayId << ", VertexBufferId " << _vertexBufferId << ", IndexBufferId " << _indexBufferId << ", " << _vertices.size() << " vertices, " << _indices.size() << " indices]";

    return stream.str();
}