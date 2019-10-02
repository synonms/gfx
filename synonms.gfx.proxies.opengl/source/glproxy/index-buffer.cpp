#include "index-buffer.h"

#include <GL\glew.h>

#include <glproxy\buffer.h>
#include <glproxy\error.h>

using namespace synonms::gfx::proxies::opengl;
using namespace synonms::gfx::proxies::opengl::enumerators;

void IndexBuffer::Bind(unsigned int id, bool throwOnError)
{
    return Buffer::Bind(TargetBuffer::ElementArrayBuffer, id, throwOnError);
}

void IndexBuffer::Draw(DrawMode drawMode, int noOfIndices, DataType dataType, bool throwOnError)
{
    if (throwOnError) Error::Clear();

    glDrawElements(static_cast<unsigned int>(drawMode), noOfIndices, static_cast<unsigned int>(dataType), nullptr);

    if (throwOnError) Error::ThrowIf({
        {GL_INVALID_ENUM, "DrawMode is invalid." },
        {GL_INVALID_VALUE, "Count is negative." },
        {GL_INVALID_OPERATION, "A geometry shader is active and DrawMode is incompatible with the input primitive type of the geometry shader OR a non-zero buffer object name is bound to an enabled array or the element array and the buffer object's data store is currently mapped." }
        });

}

unsigned int IndexBuffer::Generate(bool throwOnError)
{
    return Buffer::Generate(throwOnError);
}

void IndexBuffer::SendData(const void* data, size_t noOfBytes, DataUsage dataUsage, bool throwOnError)
{
    return Buffer::SendData(TargetBuffer::ElementArrayBuffer, data, noOfBytes, dataUsage, throwOnError);
}
