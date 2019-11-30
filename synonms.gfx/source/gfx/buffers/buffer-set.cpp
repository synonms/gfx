#include "buffer-set.h"

#include <glproxy\frame-buffer.h>

#include <utility>

using namespace synonms::gfx::buffers;
using namespace synonms::gfx::proxies;

BufferSet::BufferSet()
{
    _framebufferId = opengl::FrameBuffer::Generate(true);
}

BufferSet::BufferSet(BufferSet&& other) noexcept
    : _framebufferId(std::exchange(other._framebufferId, 0))
{
}

BufferSet& BufferSet::operator=(BufferSet&& other) noexcept
{
    _framebufferId = std::exchange(other._framebufferId, 0);

    return *this;
}

BufferSet::~BufferSet()
{
    if (_framebufferId > 0)
    {
        opengl::FrameBuffer::Delete(_framebufferId, true);
    }
}

void BufferSet::Bind() const
{
    if (_framebufferId > 0)
    {
        opengl::FrameBuffer::Bind(opengl::enumerators::FramebufferTarget::Framebuffer, _framebufferId, true);
    }
}

bool BufferSet::IsReady() const
{
    return opengl::FrameBuffer::GetStatus(opengl::enumerators::FramebufferTarget::Framebuffer) == opengl::enumerators::FramebufferStatus::Complete;
}

void BufferSet::SetColourBuffer(std::shared_ptr<ColourBuffer> buffer, int bufferIndex)
{
    _colourBuffers.emplace(std::make_pair(bufferIndex, buffer));

    opengl::FrameBuffer::AttachTexture2d(
        opengl::enumerators::FramebufferTarget::Framebuffer,
        opengl::enumerators::AttachmentPoint::Colour0,
        opengl::enumerators::TargetTexture::Texture2D,
        buffer->GetTextureId(),
        true);
}

void BufferSet::SetDepthBuffer(std::shared_ptr<DepthBuffer> buffer)
{
    _depthBuffer = buffer;

    opengl::FrameBuffer::AttachTexture2d(
        opengl::enumerators::FramebufferTarget::Framebuffer,
        opengl::enumerators::AttachmentPoint::Depth,
        opengl::enumerators::TargetTexture::Texture2D,
        buffer->GetTextureId(),
        true);

    // TODO - Call these if no colour buffer
//    opengl::FrameBuffer::SetDrawBuffer(opengl::enumerators::DrawBufferMode::None);
//    opengl::FrameBuffer::SetReadBuffer(opengl::enumerators::ReadBufferMode::None);
}

void BufferSet::Unbind() const
{
    opengl::FrameBuffer::Bind(opengl::enumerators::FramebufferTarget::Framebuffer, 0);
}
