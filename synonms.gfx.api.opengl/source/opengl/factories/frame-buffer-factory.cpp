#include "frame-buffer-factory.h"

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

    opengl::FrameBuffer::BindDefault(opengl::enumerators::FramebufferTarget::Framebuffer);

    return std::move(frameBuffer);
}
