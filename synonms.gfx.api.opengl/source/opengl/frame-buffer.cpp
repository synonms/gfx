#include "frame-buffer.h"

#include <GL\glew.h>

#include <algorithm>
#include <utility>

using namespace synonms::gfx::api::opengl;
using namespace synonms::gfx::api::opengl::enumerators;

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


void FrameBuffer::Bind(FramebufferTarget target) const
{
    glBindFramebuffer(static_cast<unsigned int>(target), _frameBufferId);
}


void FrameBuffer::AttachRenderBuffer(FramebufferTarget target, AttachmentPoint attachmentPoint, unsigned int renderBufferId)
{
    glFramebufferRenderbuffer(static_cast<unsigned int>(target), static_cast<unsigned int>(attachmentPoint), GL_RENDERBUFFER, renderBufferId);
}

void FrameBuffer::AttachTexture2d(FramebufferTarget target, AttachmentPoint attachmentPoint, TargetTexture targetTexture, unsigned int textureId)
{
    glFramebufferTexture2D(static_cast<unsigned int>(target), static_cast<unsigned int>(attachmentPoint), static_cast<unsigned int>(targetTexture), textureId, 0);
}

void FrameBuffer::BindDefault(enumerators::FramebufferTarget target)
{
    glBindFramebuffer(static_cast<unsigned int>(target), 0);
}

void FrameBuffer::Clear(AttributeBit attributeBit)
{
    glClear(static_cast<unsigned int>(attributeBit));
}

void FrameBuffer::ClearColour(float red, float green, float blue, float alpha)
{
    glClearColor(red, green, blue, alpha);
}

void FrameBuffer::ClearDepth(double value)
{
    glClearDepth(value);
}

void FrameBuffer::ClearStencil(int value)
{
    glClearStencil(value);
}

FramebufferStatus FrameBuffer::GetStatus(FramebufferTarget target)
{
    return static_cast<FramebufferStatus>(glCheckFramebufferStatus(static_cast<unsigned int>(target)));
}

void FrameBuffer::ReadColourPixels(int left, int bottom, int width, int height, enumerators::PixelReadColourFormat pixelReadFormat, enumerators::DataType dataType, void* data)
{
    glReadPixels(left, bottom, width, height, static_cast<unsigned int>(pixelReadFormat), static_cast<unsigned int>(dataType), data);
}

void FrameBuffer::ReadDepthPixels(int left, int bottom, int width, int height, enumerators::DataType dataType, void* data)
{
    glReadPixels(left, bottom, width, height, GL_DEPTH_COMPONENT, static_cast<unsigned int>(dataType), data);
}

// GL_UNSIGNED_INT_24_8 or GL_FLOAT_32_UNSIGNED_INT_24_8_REV
void FrameBuffer::ReadDepthStencilPixels(int left, int bottom, int width, int height, enumerators::DataType dataType, void* data)
{
    glReadPixels(left, bottom, width, height, GL_DEPTH_STENCIL, static_cast<unsigned int>(dataType), data);
}

void FrameBuffer::ReadStencilPixels(int left, int bottom, int width, int height, enumerators::DataType dataType, void* data)
{
    glReadPixels(left, bottom, width, height, GL_STENCIL_INDEX, static_cast<unsigned int>(dataType), data);
}

void FrameBuffer::SetDrawBuffer(DrawBufferMode mode)
{
    glDrawBuffer(static_cast<unsigned int>(mode));
}

void FrameBuffer::SetDrawBuffers(const std::vector<DrawBuffersMode>& modes)
{
    std::vector<unsigned int> attachments;

    std::transform(std::begin(modes), std::end(modes), std::back_inserter(attachments), [](DrawBuffersMode mode) { return static_cast<unsigned int>(mode); });

    glDrawBuffers(attachments.size(), attachments.data());
}

void FrameBuffer::SetReadBuffer(ReadBufferMode mode)
{
    glReadBuffer(static_cast<unsigned int>(mode));
}
