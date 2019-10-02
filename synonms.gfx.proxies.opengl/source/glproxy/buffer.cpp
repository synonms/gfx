#include "buffer.h"

#include <GL\glew.h>

#include <glproxy\error.h>

using namespace synonms::gfx::proxies::opengl;
using namespace synonms::gfx::proxies::opengl::enumerators;

void Buffer::Bind(TargetBuffer targetBuffer, unsigned int id, bool throwOnError)
{
    if (throwOnError) Error::Clear();

    glBindBuffer(static_cast<unsigned int>(targetBuffer), id);

    if (throwOnError) Error::ThrowIf({
        {GL_INVALID_ENUM, "Target is not one of the allowable values." },
        {GL_INVALID_VALUE, "Buffer is not a name previously returned from a call to glGenBuffers." }
        });
}

unsigned int Buffer::Generate(bool throwOnError)
{
    if (throwOnError) Error::Clear();

    unsigned int id;
    glGenBuffers(1, &id);

    if (throwOnError) Error::ThrowIf({
        {GL_INVALID_VALUE, "Number of buffers is negative." }
        });

    return id;
}

void Buffer::SendData(TargetBuffer targetBuffer, const void* data, size_t noOfBytes, DataUsage dataUsage, bool throwOnError)
{
    if (throwOnError) Error::Clear();

    glBufferData(static_cast<unsigned int>(targetBuffer), noOfBytes, data, static_cast<unsigned int>(dataUsage));

    if (throwOnError) Error::ThrowIf({
        {GL_INVALID_ENUM, "TargetBuffer or DataUsage is invalid" },
        {GL_INVALID_VALUE, "Size is negative." },
        {GL_INVALID_OPERATION, "Reserved buffer object name 0 is bound to target." },
        {GL_OUT_OF_MEMORY, "GL is unable to create a data store with the specified size." }
        });
}
