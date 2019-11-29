#include "depth-buffer.h"

#include <glproxy\frame-buffer.h>
#include <glproxy\texture.h>

#include <utility>

using namespace synonms::gfx::environment;

DepthBuffer::DepthBuffer(int width, int height)
{
    //_colourTextureId = proxies::opengl::Texture::Generate(true);
    //proxies::opengl::Texture::Bind(proxies::opengl::enumerators::TargetTexture::Texture2D, _colourTextureId, true);
    //proxies::opengl::Texture::SendData(
    //    proxies::opengl::enumerators::TargetTexture::Texture2D, 
    //    proxies::opengl::enumerators::TextureInternalFormat::GL_RGB,
    //    width, height,
    //    proxies::opengl::enumerators::TextureFormat::GL_RGB,
    //    proxies::opengl::enumerators::DataType::UnsignedByte,
    //    nullptr, true);
    //proxies::opengl::Texture::SetMinificationFilter(proxies::opengl::enumerators::TargetTexture::Texture2D, proxies::opengl::enumerators::MinificationFilterValue::Linear);
    //proxies::opengl::Texture::SetMagnificationFilter(proxies::opengl::enumerators::TargetTexture::Texture2D, proxies::opengl::enumerators::MagnificationFilterValue::Linear);

    //proxies::opengl::FrameBuffer::AttachTexture2d(
    //    proxies::opengl::enumerators::FramebufferTarget::Framebuffer,
    //    proxies::opengl::enumerators::AttachmentPoint::Colour0,
    //    proxies::opengl::enumerators::TargetTexture::Texture2D,
    //    _colourTextureId,
    //    true);


    _textureId = proxies::opengl::Texture::Generate(true);
    proxies::opengl::Texture::Bind(proxies::opengl::enumerators::TargetTexture::Texture2D, _textureId, true);
    proxies::opengl::Texture::SendData(
        proxies::opengl::enumerators::TargetTexture::Texture2D,
        proxies::opengl::enumerators::TextureInternalFormat::GL_DEPTH_COMPONENT32F,
        width, height,
        proxies::opengl::enumerators::TextureFormat::GL_DEPTH_COMPONENT,
        proxies::opengl::enumerators::DataType::Float,
        nullptr, true);
    proxies::opengl::Texture::SetMinificationFilter(proxies::opengl::enumerators::TargetTexture::Texture2D, proxies::opengl::enumerators::MinificationFilterValue::Linear);
    proxies::opengl::Texture::SetMagnificationFilter(proxies::opengl::enumerators::TargetTexture::Texture2D, proxies::opengl::enumerators::MagnificationFilterValue::Linear);
    proxies::opengl::Texture::SetCompareMode(proxies::opengl::enumerators::TargetTexture::Texture2D, proxies::opengl::enumerators::TextureCompareMode::CompareRefToTexture);
    proxies::opengl::Texture::SetCompareFunc(proxies::opengl::enumerators::TargetTexture::Texture2D, proxies::opengl::enumerators::TextureCompareFunc::LessThanOrEqual);
    proxies::opengl::Texture::SetWrapModeS(proxies::opengl::enumerators::TargetTexture::Texture2D, proxies::opengl::enumerators::TextureWrapMode::ClampToEdge);
    proxies::opengl::Texture::SetWrapModeT(proxies::opengl::enumerators::TargetTexture::Texture2D, proxies::opengl::enumerators::TextureWrapMode::ClampToEdge);

    _framebufferId = proxies::opengl::FrameBuffer::Generate(true);
    proxies::opengl::FrameBuffer::Bind(proxies::opengl::enumerators::FramebufferTarget::Framebuffer, _framebufferId, true);
    proxies::opengl::FrameBuffer::AttachTexture2d(
        proxies::opengl::enumerators::FramebufferTarget::Framebuffer,
        proxies::opengl::enumerators::AttachmentPoint::Depth,
        proxies::opengl::enumerators::TargetTexture::Texture2D,
        _textureId,
        true);
    proxies::opengl::FrameBuffer::SetDrawBuffer(proxies::opengl::enumerators::DrawBufferMode::None);
}

DepthBuffer::DepthBuffer(DepthBuffer&& other) noexcept
    : _framebufferId(std::exchange(other._framebufferId, 0))
    , _textureId(std::exchange(other._textureId, 0))
{
}

DepthBuffer& DepthBuffer::operator=(DepthBuffer&& other) noexcept
{
    _framebufferId = std::exchange(other._framebufferId, 0);
    _textureId = std::exchange(other._textureId, 0);

    return *this;
}

DepthBuffer::~DepthBuffer()
{
    if (_framebufferId > 0) 
    {
        proxies::opengl::FrameBuffer::Delete(_framebufferId, true);
    }
}

void DepthBuffer::Bind() const
{
    if (_framebufferId > 0) 
    {
        proxies::opengl::FrameBuffer::Bind(proxies::opengl::enumerators::FramebufferTarget::Framebuffer, _framebufferId, true);
    }
}

bool DepthBuffer::IsReady() const
{
    return proxies::opengl::FrameBuffer::GetStatus(proxies::opengl::enumerators::FramebufferTarget::Framebuffer) == proxies::opengl::enumerators::FramebufferStatus::GL_FRAMEBUFFER_COMPLETE;
}
