#include "vertex-array.h"

#include <GL\glew.h>

#include <utility>

using namespace synonms::gfx::api::opengl;

VertexArray::VertexArray()
{
    glGenVertexArrays(1, &_vertexArrayId);
}

VertexArray::VertexArray(VertexArray&& other) noexcept
    : _vertexArrayId(std::exchange(other._vertexArrayId, 0))
{
}

VertexArray& VertexArray::operator=(VertexArray&& other) noexcept
{
    _vertexArrayId = std::exchange(other._vertexArrayId, 0);

    return *this;
}

VertexArray::~VertexArray()
{
    if (_vertexArrayId > 0) {
        glDeleteVertexArrays(1, &_vertexArrayId);
    }
}


void VertexArray::Bind() const
{
    glBindVertexArray(_vertexArrayId);
}
