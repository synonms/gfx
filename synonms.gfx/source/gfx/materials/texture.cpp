#include "texture.h"

#include <glproxy\texture.h>

#include <vendor\stb_image\stb-image.h>

using namespace synonms::gfx::materials;

Texture::Texture(const std::string& filePath)
    : _filePath(filePath)
{
    // OpenGL expects images with 0,0 at bottom left which isn't how PNG stores the data, so we need to flip it
    stbi_set_flip_vertically_on_load(1);
    auto data = stbi_load(filePath.c_str(), &_width, &_height, &_bitsPerPixel, 4); // 4 = RGBA

    if (!data)
    {
        auto message = stbi_failure_reason();
        throw std::exception(message);
    }

    _textureId = proxies::opengl::Texture::Generate(true);
    Bind();

    proxies::opengl::Texture::SetMinificationFilter(proxies::opengl::enumerators::TargetTexture::Texture2D, proxies::opengl::enumerators::MinificationFilterValue::Linear);
    proxies::opengl::Texture::SetMagnificationFilter(proxies::opengl::enumerators::TargetTexture::Texture2D, proxies::opengl::enumerators::MagnificationFilterValue::Linear);
    proxies::opengl::Texture::SetWrapModeS(proxies::opengl::enumerators::TargetTexture::Texture2D, proxies::opengl::enumerators::TextureWrapMode::ClampToEdge);
    proxies::opengl::Texture::SetWrapModeT(proxies::opengl::enumerators::TargetTexture::Texture2D, proxies::opengl::enumerators::TextureWrapMode::ClampToEdge);

    proxies::opengl::Texture::SendData(
        proxies::opengl::enumerators::TargetTexture::Texture2D, 
        proxies::opengl::enumerators::TextureInternalFormat::GL_RGB8,
        _width, _height,
        proxies::opengl::enumerators::TextureFormat::GL_RGBA,
        proxies::opengl::enumerators::DataType::UnsignedByte,
        data, true);

    Unbind();

    if (data)
    {
        stbi_image_free(data);
    }
    else 
    {
        throw std::exception("Image data not loaded");
    }
}

Texture::Texture(Texture&& other) noexcept
    : _textureId(std::exchange(other._textureId, 0))
    , _filePath(std::exchange(other._filePath, ""))
    , _width(std::exchange(other._width, 0))
    , _height(std::exchange(other._height, 0))
    , _bitsPerPixel(std::exchange(other._bitsPerPixel, 0))
{
}

Texture& Texture::operator=(Texture&& other) noexcept
{
    _textureId = std::exchange(other._textureId, 0);
    _filePath = std::exchange(other._filePath, "");
    _width = std::exchange(other._width, 0);
    _height = std::exchange(other._height, 0);
    _bitsPerPixel = std::exchange(other._bitsPerPixel, 0);

    return *this;
}

Texture::~Texture()
{
    if (_textureId > 0) {
        proxies::opengl::Texture::Delete(_textureId, true);
    }
}

void Texture::Bind(unsigned int slot) const
{
    if (_textureId > 0) {
        proxies::opengl::Texture::ActivateSlot(slot);
        proxies::opengl::Texture::Bind(proxies::opengl::enumerators::TargetTexture::Texture2D, _textureId, true);
    }
}

int Texture::GetHeight() const
{
    return _height;
}

int Texture::GetWidth() const
{
    return _width;
}

void Texture::Unbind()
{
    proxies::opengl::Texture::Unbind(proxies::opengl::enumerators::TargetTexture::Texture2D, true);
}
