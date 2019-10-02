#include "vertex-buffer.h"

#include <GL\glew.h>

#include <glproxy\buffer.h>

using namespace synonms::gfx::proxies::opengl;
using namespace synonms::gfx::proxies::opengl::enumerators;

void VertexBuffer::Bind(unsigned int vertexBufferId, bool throwOnError)
{
    return Buffer::Bind(TargetBuffer::ArrayBuffer, vertexBufferId, throwOnError);
}

unsigned int VertexBuffer::Generate(bool throwOnError)
{
    return Buffer::Generate(throwOnError);
}

void VertexBuffer::SendData(const void* data, size_t noOfBytes, DataUsage dataUsage, bool throwOnError)
{
    return Buffer::SendData(TargetBuffer::ArrayBuffer, data, noOfBytes, dataUsage, throwOnError);
}
