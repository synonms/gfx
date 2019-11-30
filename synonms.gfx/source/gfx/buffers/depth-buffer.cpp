#include "depth-buffer.h"

#include <glproxy\texture.h>

#include <utility>

using namespace synonms::gfx::buffers;
using namespace synonms::gfx::proxies;

DepthBuffer::DepthBuffer(int width, int height)
    : _width(width)
    , _height(height)
{
    _textureId = opengl::Texture::Generate(true);
    opengl::Texture::ActivateSlot(0);
    opengl::Texture::Bind(opengl::enumerators::TargetTexture::Texture2D, _textureId, true);
    opengl::Texture::SendData(
        opengl::enumerators::TargetTexture::Texture2D,
        opengl::enumerators::TextureInternalFormat::GL_DEPTH_COMPONENT32F,
        width, height,
        opengl::enumerators::TextureFormat::GL_DEPTH_COMPONENT,
        opengl::enumerators::DataType::Float,
        nullptr, true);
    opengl::Texture::SetMinificationFilter(opengl::enumerators::TargetTexture::Texture2D, opengl::enumerators::MinificationFilterValue::Linear);
    opengl::Texture::SetMagnificationFilter(opengl::enumerators::TargetTexture::Texture2D, opengl::enumerators::MagnificationFilterValue::Linear);
    opengl::Texture::SetCompareMode(opengl::enumerators::TargetTexture::Texture2D, opengl::enumerators::TextureCompareMode::CompareRefToTexture);
    opengl::Texture::SetCompareFunc(opengl::enumerators::TargetTexture::Texture2D, opengl::enumerators::TextureCompareFunc::LessThanOrEqual);
    opengl::Texture::SetWrapModeS(opengl::enumerators::TargetTexture::Texture2D, opengl::enumerators::TextureWrapMode::ClampToEdge);
    opengl::Texture::SetWrapModeT(opengl::enumerators::TargetTexture::Texture2D, opengl::enumerators::TextureWrapMode::ClampToEdge);
}

DepthBuffer::DepthBuffer(DepthBuffer&& other) noexcept
    : _textureId(std::exchange(other._textureId, 0))
    , _width(std::exchange(other._width, 0))
    , _height(std::exchange(other._height, 0))
{
}

DepthBuffer& DepthBuffer::operator=(DepthBuffer&& other) noexcept
{
    _textureId = std::exchange(other._textureId, 0);
    _width = std::exchange(other._width, 0);
    _height = std::exchange(other._height, 0);

    return *this;
}

DepthBuffer::~DepthBuffer()
{
    if (_textureId > 0) 
    {
        opengl::Texture::Delete(_textureId, true);
    }
}
