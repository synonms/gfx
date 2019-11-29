#include "frame-buffer.h"

#include <GL\glew.h>

#include <glproxy\error.h>

using namespace synonms::gfx::proxies::opengl;
using namespace synonms::gfx::proxies::opengl::enumerators;

void FrameBuffer::AttachTexture2d(FramebufferTarget target, AttachmentPoint attachmentPoint, TargetTexture targetTexture, unsigned int textureId, bool throwOnError)
{
    if (throwOnError) Error::Clear();

    glFramebufferTexture2D(static_cast<unsigned int>(target), static_cast<unsigned int>(attachmentPoint), static_cast<unsigned int>(targetTexture), textureId, 0);

    if (throwOnError) Error::ThrowIf({
        {GL_INVALID_ENUM, "Target or attachmentPoint is not one of the allowable values." },
        {GL_INVALID_OPERATION, "Target is zero or not compatible with texture." }
        });
}

void FrameBuffer::Bind(FramebufferTarget target, unsigned int framebufferId, bool throwOnError)
{
    if (throwOnError) Error::Clear();

    glBindFramebuffer(static_cast<unsigned int>(target), framebufferId);

    if (throwOnError) Error::ThrowIf({
        {GL_INVALID_ENUM, "Target is not one of the allowable values." },
        {GL_INVALID_OPERATION , "Buffer is not a name previously returned from a call to glGenFramebuffers." }
        });
}

void FrameBuffer::Delete(unsigned int framebufferId, bool throwOnError)
{
    if (throwOnError) Error::Clear();

    glDeleteFramebuffers(1, &framebufferId);

    if (throwOnError) Error::ThrowIf({
        {GL_INVALID_VALUE, "Size is negative." }
        });
}

unsigned int FrameBuffer::Generate(bool throwOnError)
{
    if (throwOnError) Error::Clear();

    unsigned int id;
    glGenFramebuffers(1, &id);

    if (throwOnError) Error::ThrowIf({
        {GL_INVALID_VALUE, "Number of buffers is negative." }
        });

    return id;
}

FramebufferStatus GetStatus(FramebufferTarget target, bool throwOnError)
{
    if (throwOnError) Error::Clear();

    auto status = glCheckFramebufferStatus(static_cast<unsigned int>(target));

    if (throwOnError) Error::ThrowIf({
        {GL_INVALID_ENUM, "Target is invalid." }
        });

    return static_cast<FramebufferStatus>(status);
}

void FrameBuffer::SetDrawBuffer(DrawBufferMode mode, bool throwOnError)
{
    if (throwOnError) Error::Clear();

    glDrawBuffer(static_cast<unsigned int>(mode));

    if (throwOnError) Error::ThrowIf({
        {GL_INVALID_ENUM, "Mode is not one of the allowable values." },
        {GL_INVALID_OPERATION, "Mode specifies a buffer that does not exist." }
        });
}

void FrameBuffer::SetReadBuffer(ReadBufferMode mode, bool throwOnError)
{
    if (throwOnError) Error::Clear();

    glReadBuffer(static_cast<unsigned int>(mode));

    if (throwOnError) Error::ThrowIf({
        {GL_INVALID_ENUM, "Mode is not one of the allowable values." },
        {GL_INVALID_OPERATION, "Mode specifies a buffer that does not exist." }
        });
}
