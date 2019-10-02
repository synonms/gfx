#include "vertex-array.h"

#include <GL\glew.h>

#include <glproxy\error.h>

using namespace synonms::gfx::proxies::opengl;

void VertexArray::Bind(unsigned int vertexArrayId, bool throwOnError)
{
    if (throwOnError) Error::Clear();

    glBindVertexArray(vertexArrayId);

    if (throwOnError) Error::ThrowIf({
        {GL_INVALID_OPERATION, "VertexArray is not zero or the name of a vertex array object previously returned from a call to glGenVertexArrays." }
        });
}

unsigned int VertexArray::Generate(bool throwOnError)
{
    if (throwOnError) Error::Clear();

    unsigned int vertexArrayId;
    glGenVertexArrays(1, &vertexArrayId);

    if (throwOnError) Error::ThrowIf({
        {GL_INVALID_VALUE, "Count is negative." }
        });

    return vertexArrayId;
}
