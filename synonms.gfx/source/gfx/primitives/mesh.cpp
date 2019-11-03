#include "mesh.h"

#include <gfx\enumerators\data-type.h>

#include <glproxy\index-buffer.h>
#include <glproxy\vertex-array.h>
#include <glproxy\vertex-attribute-array.h>
#include <glproxy\vertex-buffer.h>

#include <iostream>
#include <sstream>

using namespace synonms::gfx::primitives;
using namespace synonms::gfx::enumerators;

Mesh::Mesh(const VertexDefinition& vertexDefinition, float* vertexData, unsigned int noOfVertices, unsigned int* indexData, unsigned int noOfIndices)
    : _noOfVertices(noOfVertices)
    , _noOfIndices(noOfIndices)
{
    const auto vertexSize = vertexDefinition.Size();

    _vertexArrayId = proxies::opengl::VertexArray::Generate(true);
    proxies::opengl::VertexArray::Bind(_vertexArrayId, true);

    _vertexBufferId = proxies::opengl::VertexBuffer::Generate(true);
    proxies::opengl::VertexBuffer::Bind(_vertexBufferId, true);
    proxies::opengl::VertexBuffer::SendData(vertexData, (size_t)_noOfVertices * (size_t)vertexSize, proxies::opengl::enumerators::DataUsage::StaticDraw, true);

    const auto& attributes = vertexDefinition.GetAttributes();
    auto offset = 0u;
    for (auto index = 0; index < attributes.size(); ++index)
    {
        const auto& attribute = attributes[index];

        std::cout << "Configuring attribute " << index << " with " << attribute.GetNoOfComponents() << " components and offset " << offset << std::endl;

        proxies::opengl::VertexAttributeArray::Enable(index, true);
        proxies::opengl::VertexAttributeArray::Configure(index, attribute.GetNoOfComponents(), static_cast<proxies::opengl::enumerators::DataType>(DataTypeMapper::ConvertForProxy(attribute.GetDataType())), vertexSize, attribute.GetIsNormalised(), offset, true);
        offset += attribute.GetNoOfBytes();
    }

    _indexBufferId = proxies::opengl::IndexBuffer::Generate(true);
    proxies::opengl::IndexBuffer::Bind(_indexBufferId, true);
    proxies::opengl::IndexBuffer::SendData(indexData, _noOfIndices * sizeof(unsigned int), proxies::opengl::enumerators::DataUsage::StaticDraw, true);
}

void Mesh::Draw()
{
    proxies::opengl::VertexArray::Bind(_vertexArrayId, true);

    proxies::opengl::IndexBuffer::Bind(_indexBufferId, true);
    proxies::opengl::IndexBuffer::Draw(proxies::opengl::enumerators::DrawMode::Triangles, _noOfIndices, proxies::opengl::enumerators::DataType::UnsignedInt, true);
}

std::string Mesh::ToString()
{
    std::stringstream stream;
    stream << "[Mesh: VertexArrayId " << _vertexArrayId << ", VertexBufferId " << _vertexBufferId << ", IndexBufferId " << _indexBufferId << ", " << _noOfVertices << " vertices, " << _noOfIndices << " indices]";

    return stream.str();
}