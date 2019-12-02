#include "frame-buffer.h"

#include <GL\glew.h>

#include <glproxy\error.h>

using namespace synonms::gfx::proxies::opengl;
using namespace synonms::gfx::proxies::opengl::enumerators;

FrameBuffer::FrameBuffer()
{
    glGenFramebuffers(1, &_frameBufferId);
}

FrameBuffer::FrameBuffer(FrameBuffer&& other) noexcept
    : _frameBufferId(std::exchange(other._frameBufferId, 0))
{
}

FrameBuffer& FrameBuffer::operator=(FrameBuffer&& other) noexcept
{
    _frameBufferId = std::exchange(other._frameBufferId, 0);

    return *this;
}

FrameBuffer::~FrameBuffer()
{
    if (_frameBufferId > 0) {
        glDeleteFramebuffers(1, &_frameBufferId);
    }
}


void FrameBuffer::Bind(FramebufferTarget target, bool throwOnError) const
{
    if (throwOnError) Error::Clear();

    glBindFramebuffer(static_cast<unsigned int>(target), _frameBufferId);

    if (throwOnError) Error::ThrowIf({
        {GL_INVALID_ENUM, "Target is not one of the allowable values." },
        {GL_INVALID_OPERATION , "Buffer is not a name previously returned from a call to glGenFramebuffers." }
        });
}


void FrameBuffer::AttachRenderBuffer(FramebufferTarget target, AttachmentPoint attachmentPoint, unsigned int renderBufferId, bool throwOnError)
{
    if (throwOnError) Error::Clear();

    glFramebufferRenderbuffer(static_cast<unsigned int>(target), static_cast<unsigned int>(attachmentPoint), GL_RENDERBUFFER, renderBufferId);

    if (throwOnError) Error::ThrowIf({
        {GL_INVALID_ENUM, "Target is not one of the allowable values." },
        {GL_INVALID_OPERATION, "Framebuffer is not bound to target." }
        });
}

void FrameBuffer::AttachTexture2d(FramebufferTarget target, AttachmentPoint attachmentPoint, TargetTexture targetTexture, unsigned int textureId, bool throwOnError)
{
    if (throwOnError) Error::Clear();

    glFramebufferTexture2D(static_cast<unsigned int>(target), static_cast<unsigned int>(attachmentPoint), static_cast<unsigned int>(targetTexture), textureId, 0);

    if (throwOnError) Error::ThrowIf({
        {GL_INVALID_ENUM, "Target or attachmentPoint is not one of the allowable values." },
        {GL_INVALID_OPERATION, "Target is zero or not compatible with texture." }
        });
}

void FrameBuffer::BindDefault(enumerators::FramebufferTarget target, bool throwOnError)
{
    if (throwOnError) Error::Clear();

    glBindFramebuffer(static_cast<unsigned int>(target), 0);

    if (throwOnError) Error::ThrowIf({
        {GL_INVALID_ENUM, "Target is not one of the allowable values." },
        {GL_INVALID_OPERATION , "Buffer is not a name previously returned from a call to glGenFramebuffers." }
        });
}

FramebufferStatus FrameBuffer::GetStatus(FramebufferTarget target, bool throwOnError)
{
    if (throwOnError) Error::Clear();

    auto status = glCheckFramebufferStatus(static_cast<unsigned int>(target));

    if (throwOnError) Error::ThrowIf({
        {GL_INVALID_ENUM, "Target is invalid." }
        });

    return static_cast<FramebufferStatus>(status);
}

void FrameBuffer::ReadColourPixels(int left, int bottom, int width, int height, enumerators::PixelReadColourFormat pixelReadFormat, enumerators::DataType dataType, void* data, bool throwOnError)
{
    if (throwOnError) Error::Clear();

    glReadPixels(left, bottom, width, height, static_cast<unsigned int>(pixelReadFormat), static_cast<unsigned int>(dataType), data);

    if (throwOnError) Error::ThrowIf({
        {GL_INVALID_ENUM, "PixelReadFormat or DataType are invalid." },
        {GL_INVALID_VALUE, "Dimensions are negative"}
        // TODO
        });
}

void FrameBuffer::ReadDepthPixels(int left, int bottom, int width, int height, enumerators::DataType dataType, void* data, bool throwOnError)
{
    if (throwOnError) Error::Clear();

    glReadPixels(left, bottom, width, height, GL_DEPTH_COMPONENT, static_cast<unsigned int>(dataType), data);

    if (throwOnError) Error::ThrowIf({
        {GL_INVALID_ENUM, "PixelReadFormat or DataType are invalid." },
        {GL_INVALID_VALUE, "Dimensions are negative"}
        // TODO
        });
}

// GL_UNSIGNED_INT_24_8 or GL_FLOAT_32_UNSIGNED_INT_24_8_REV
void FrameBuffer::ReadDepthStencilPixels(int left, int bottom, int width, int height, enumerators::DataType dataType, void* data, bool throwOnError)
{
    if (throwOnError) Error::Clear();

    glReadPixels(left, bottom, width, height, GL_DEPTH_STENCIL, static_cast<unsigned int>(dataType), data);

    if (throwOnError) Error::ThrowIf({
        {GL_INVALID_ENUM, "PixelReadFormat or DataType are invalid." },
        {GL_INVALID_VALUE, "Dimensions are negative"}
        // TODO
        });
}

void FrameBuffer::ReadStencilPixels(int left, int bottom, int width, int height, enumerators::DataType dataType, void* data, bool throwOnError)
{
    if (throwOnError) Error::Clear();

    glReadPixels(left, bottom, width, height, GL_STENCIL_INDEX, static_cast<unsigned int>(dataType), data);

    if (throwOnError) Error::ThrowIf({
        {GL_INVALID_ENUM, "PixelReadFormat or DataType are invalid." },
        {GL_INVALID_VALUE, "Dimensions are negative"}
        // TODO
        });
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
