#include "colour-buffer.h"

#include <glproxy\texture.h>

#include <utility>

using namespace synonms::gfx::buffers;
using namespace synonms::gfx::proxies;

ColourBuffer::ColourBuffer(int width, int height)
    : _width(width)
    , _height(height)
{
    _textureId = opengl::Texture::Generate(true);
    opengl::Texture::ActivateSlot(0);
    opengl::Texture::Bind(opengl::enumerators::TargetTexture::Texture2D, _textureId, true);
    opengl::Texture::SendData(
        opengl::enumerators::TargetTexture::Texture2D, 
        opengl::enumerators::TextureInternalFormat::GL_RGB,
        width, height,
        opengl::enumerators::TextureFormat::GL_RGB,
        opengl::enumerators::DataType::UnsignedByte,
        nullptr, true);
    opengl::Texture::SetMinificationFilter(opengl::enumerators::TargetTexture::Texture2D, opengl::enumerators::MinificationFilterValue::Linear);
    opengl::Texture::SetMagnificationFilter(opengl::enumerators::TargetTexture::Texture2D, opengl::enumerators::MagnificationFilterValue::Linear);
    opengl::Texture::SetWrapModeS(opengl::enumerators::TargetTexture::Texture2D, opengl::enumerators::TextureWrapMode::ClampToEdge);
    opengl::Texture::SetWrapModeT(opengl::enumerators::TargetTexture::Texture2D, opengl::enumerators::TextureWrapMode::ClampToEdge);
}

ColourBuffer::ColourBuffer(ColourBuffer&& other) noexcept
    : _textureId(std::exchange(other._textureId, 0))
    , _width(std::exchange(other._width, 0))
    , _height(std::exchange(other._height, 0))
{
}

ColourBuffer& ColourBuffer::operator=(ColourBuffer&& other) noexcept
{
    _textureId = std::exchange(other._textureId, 0);
    _width = std::exchange(other._width, 0);
    _height = std::exchange(other._height, 0);

    return *this;
}

ColourBuffer::~ColourBuffer()
{
    if (_textureId > 0)
    {
        opengl::Texture::Delete(_textureId, true);
    }
}

void ColourBuffer::Bind() const
{
    opengl::Texture::ActivateSlot(0);
    opengl::Texture::Bind(opengl::enumerators::TargetTexture::Texture2D, _textureId, true);
}