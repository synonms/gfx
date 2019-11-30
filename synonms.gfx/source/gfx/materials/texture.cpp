#include "texture.h"

#include <glproxy\texture.h>

#include <vendor\stb_image\stb-image.h>

using namespace synonms::gfx::enumerators;
using namespace synonms::gfx::materials;
using namespace synonms::gfx::proxies;

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

    _textureId = opengl::Texture::Generate(true);
    Bind();

    opengl::Texture::SetMinificationFilter(opengl::enumerators::TargetTexture::Texture2D, opengl::enumerators::MinificationFilterValue::Linear);
    opengl::Texture::SetMagnificationFilter(opengl::enumerators::TargetTexture::Texture2D, opengl::enumerators::MagnificationFilterValue::Linear);
    opengl::Texture::SetWrapModeS(opengl::enumerators::TargetTexture::Texture2D, opengl::enumerators::TextureWrapMode::ClampToEdge);
    opengl::Texture::SetWrapModeT(opengl::enumerators::TargetTexture::Texture2D, opengl::enumerators::TextureWrapMode::ClampToEdge);

    opengl::Texture::SendData(
        opengl::enumerators::TargetTexture::Texture2D, 
        opengl::enumerators::TextureInternalFormat::GL_RGB8,
        _width, _height,
        opengl::enumerators::TextureFormat::GL_RGBA,
        opengl::enumerators::DataType::UnsignedByte,
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
        opengl::Texture::Delete(_textureId, true);
    }
}

void Texture::Bind(TextureSlot slot) const
{
    if (_textureId > 0) {
        opengl::Texture::ActivateSlot(static_cast<unsigned int>(slot));
        opengl::Texture::Bind(opengl::enumerators::TargetTexture::Texture2D, _textureId, true);
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
