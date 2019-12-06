#include "index-buffer.h"

#include <GL\glew.h>

#include <utility>

using namespace synonms::gfx::api::opengl;
using namespace synonms::gfx::api::opengl::enumerators;

IndexBuffer::IndexBuffer()
{
    glGenBuffers(1, &_indexBufferId);
}

IndexBuffer::IndexBuffer(IndexBuffer&& other) noexcept
    : _indexBufferId(std::exchange(other._indexBufferId, 0))
{
}

IndexBuffer& IndexBuffer::operator=(IndexBuffer&& other) noexcept
{
    _indexBufferId = std::exchange(other._indexBufferId, 0);

    return *this;
}

IndexBuffer::~IndexBuffer()
{
    if (_indexBufferId > 0) {
        glDeleteBuffers(1, &_indexBufferId);
    }
}


void IndexBuffer::Bind() const
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _indexBufferId);
}


void IndexBuffer::Draw(DrawMode drawMode, int noOfIndices, DataType dataType)
{
    glDrawElements(static_cast<unsigned int>(drawMode), noOfIndices, static_cast<unsigned int>(dataType), nullptr);
}

void IndexBuffer::SendData(const void* data, size_t noOfBytes, DataUsage dataUsage)
{
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, noOfBytes, data, static_cast<unsigned int>(dataUsage));
}
