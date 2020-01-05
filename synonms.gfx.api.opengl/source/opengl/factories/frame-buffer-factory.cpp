#include "frame-buffer-factory.h"

#include <opengl\opengl-exception.h>

using namespace synonms::gfx::api::opengl;
using namespace synonms::gfx::api::opengl::enumerators;
using namespace synonms::gfx::api::opengl::factories;

std::unique_ptr<FrameBuffer> FrameBufferFactory::CreateOffscreenBuffer(int width, int height, unsigned int colourTextureId, unsigned int depthStencilRenderBufferId)
{
    auto frameBuffer = std::make_unique<opengl::FrameBuffer>();

    frameBuffer->Bind(FramebufferTarget::Framebuffer);

    opengl::FrameBuffer::AttachTexture2d(
        opengl::enumerators::FramebufferTarget::Framebuffer,
        opengl::enumerators::AttachmentPoint::Colour0,
        opengl::enumerators::TargetTexture::Texture2D,
        colourTextureId);

    opengl::FrameBuffer::AttachRenderBuffer(
        opengl::enumerators::FramebufferTarget::Framebuffer,
        opengl::enumerators::AttachmentPoint::DepthStencil,
        depthStencilRenderBufferId);

    if (opengl::FrameBuffer::GetStatus(opengl::enumerators::FramebufferTarget::Framebuffer) != opengl::enumerators::FramebufferStatus::Complete)
    {
        throw new OpenglException({ {0u, "Incomplete FrameBuffer"} });
    }

    opengl::FrameBuffer::BindDefault(opengl::enumerators::FramebufferTarget::Framebuffer);

    return std::move(frameBuffer);
}

std::unique_ptr<FrameBuffer> FrameBufferFactory::CreateShadowmapBuffer(int width, int height, unsigned int depthTextureId, unsigned int colourTextureId)
{
    auto frameBuffer = std::make_unique<opengl::FrameBuffer>();

    frameBuffer->Bind(FramebufferTarget::Framebuffer);

    opengl::FrameBuffer::AttachTexture2d(
        opengl::enumerators::FramebufferTarget::Framebuffer,
        opengl::enumerators::AttachmentPoint::Depth,
        opengl::enumerators::TargetTexture::Texture2D,
        depthTextureId);

    if (colourTextureId > 0)
    {
        opengl::FrameBuffer::AttachTexture2d(
            opengl::enumerators::FramebufferTarget::Framebuffer,
            opengl::enumerators::AttachmentPoint::Colour0,
            opengl::enumerators::TargetTexture::Texture2D,
            colourTextureId);
    }
    else 
    {
        opengl::FrameBuffer::SetDrawBuffer(DrawBufferMode::None);
        opengl::FrameBuffer::SetReadBuffer(ReadBufferMode::None);
    }

    if (opengl::FrameBuffer::GetStatus(opengl::enumerators::FramebufferTarget::Framebuffer) != opengl::enumerators::FramebufferStatus::Complete)
    {
        throw new OpenglException({ {0u, "Incomplete FrameBuffer"} });
    }

    opengl::FrameBuffer::BindDefault(opengl::enumerators::FramebufferTarget::Framebuffer);

    return std::move(frameBuffer);
}

std::unique_ptr<FrameBuffer> FrameBufferFactory::CreateGBuffer(int width, int height, unsigned int positionTextureId, unsigned int normalTextureId, unsigned int albedoSpecularTextureId, unsigned int depthStencilRenderBufferId)
{
    auto frameBuffer = std::make_unique<opengl::FrameBuffer>();

    frameBuffer->Bind(FramebufferTarget::Framebuffer);

    opengl::FrameBuffer::AttachTexture2d(
        opengl::enumerators::FramebufferTarget::Framebuffer,
        opengl::enumerators::AttachmentPoint::Colour0,
        opengl::enumerators::TargetTexture::Texture2D,
        positionTextureId);

    opengl::FrameBuffer::AttachTexture2d(
        opengl::enumerators::FramebufferTarget::Framebuffer,
        opengl::enumerators::AttachmentPoint::Colour1,
        opengl::enumerators::TargetTexture::Texture2D,
        normalTextureId);

    opengl::FrameBuffer::AttachTexture2d(
        opengl::enumerators::FramebufferTarget::Framebuffer,
        opengl::enumerators::AttachmentPoint::Colour2,
        opengl::enumerators::TargetTexture::Texture2D,
        albedoSpecularTextureId);

    opengl::FrameBuffer::AttachRenderBuffer(
        opengl::enumerators::FramebufferTarget::Framebuffer,
        opengl::enumerators::AttachmentPoint::DepthStencil,
        depthStencilRenderBufferId);

    opengl::FrameBuffer::SetDrawBuffers({ DrawBuffersMode::Colour0, DrawBuffersMode::Colour1, DrawBuffersMode::Colour2 });

    if (opengl::FrameBuffer::GetStatus(opengl::enumerators::FramebufferTarget::Framebuffer) != opengl::enumerators::FramebufferStatus::Complete)
    {
        throw new OpenglException({ {0u, "Incomplete FrameBuffer"} });
    }

    opengl::FrameBuffer::BindDefault(opengl::enumerators::FramebufferTarget::Framebuffer);

    return std::move(frameBuffer);
}
