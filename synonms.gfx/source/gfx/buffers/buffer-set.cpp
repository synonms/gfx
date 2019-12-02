#include "buffer-set.h"

#include <glproxy\frame-buffer.h>
#include <glproxy\factories\render-buffer-factory.h>
#include <glproxy\factories\texture-factory.h>

#include <utility>

using namespace synonms::gfx::buffers;
using namespace synonms::gfx::proxies;

BufferSet::BufferSet(int width, int height)
{
    _frameBuffer = std::make_unique<opengl::FrameBuffer>();

    Bind();

    _colourTextures.emplace(std::make_pair(0, opengl::factories::TextureFactory::CreateColour(width, height)));

    opengl::FrameBuffer::AttachTexture2d(
        opengl::enumerators::FramebufferTarget::Framebuffer,
        opengl::enumerators::AttachmentPoint::Colour0,
        opengl::enumerators::TargetTexture::Texture2D,
        _colourTextures.at(0)->GetTextureId(),
        true);

    _depthStencilBuffer = opengl::factories::RenderBufferFactory::CreateDepthStencilBuffer(width, height);

    opengl::FrameBuffer::AttachRenderBuffer(
        opengl::enumerators::FramebufferTarget::Framebuffer,
        opengl::enumerators::AttachmentPoint::DepthStencil,
        _depthStencilBuffer->GetRenderBufferId(),
        true);

    opengl::FrameBuffer::BindDefault(opengl::enumerators::FramebufferTarget::Framebuffer);
}

BufferSet::BufferSet(BufferSet&& other) noexcept
    : _frameBuffer(std::exchange(other._frameBuffer, nullptr))
    , _colourTextures(std::exchange(other._colourTextures, {}))
    , _depthStencilBuffer(std::exchange(other._depthStencilBuffer, nullptr))
{
}

BufferSet& BufferSet::operator=(BufferSet&& other) noexcept
{
    _frameBuffer = std::exchange(other._frameBuffer, nullptr);
    _colourTextures = std::exchange(other._colourTextures, {});
    _depthStencilBuffer = std::exchange(other._depthStencilBuffer, nullptr);

    return *this;
}

BufferSet::~BufferSet()
{
}

void BufferSet::Bind() const
{
    if (_frameBuffer != nullptr)
    {
        _frameBuffer->Bind(opengl::enumerators::FramebufferTarget::Framebuffer);
    }
}
