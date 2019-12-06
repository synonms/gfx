#include "vertex-buffer.h"

#include <GL\glew.h>

#include <utility>

using namespace synonms::gfx::api::opengl;
using namespace synonms::gfx::api::opengl::enumerators;

VertexBuffer::VertexBuffer()
{
    glGenBuffers(1, &_vertexBufferId);
}

VertexBuffer::VertexBuffer(VertexBuffer&& other) noexcept
    : _vertexBufferId(std::exchange(other._vertexBufferId, 0))
{
}

VertexBuffer& VertexBuffer::operator=(VertexBuffer&& other) noexcept
{
    _vertexBufferId = std::exchange(other._vertexBufferId, 0);

    return *this;
}

VertexBuffer::~VertexBuffer()
{
    if (_vertexBufferId > 0) {
        glDeleteBuffers(1, &_vertexBufferId);
    }
}


void VertexBuffer::Bind() const
{
    glBindBuffer(GL_ARRAY_BUFFER, _vertexBufferId);
}


void VertexBuffer::SendData(const void* data, size_t noOfBytes, DataUsage dataUsage)
{
    glBufferData(GL_ARRAY_BUFFER, noOfBytes, data, static_cast<unsigned int>(dataUsage));
}
