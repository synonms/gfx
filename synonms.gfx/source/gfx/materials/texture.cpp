#include "texture.h"

#include <glproxy\texture.h>

#include <vendor\stb_image\stb-image.h>

using namespace synonms::gfx::materials;

Texture::Texture(const std::string& filePath)
    : _filePath(filePath)
{
    // OpenGL expects images with 0,0 at bottom left which isn't how PNG stores the data, so we need to flip it
    stbi_set_flip_vertically_on_load(1);
    _data = stbi_load(filePath.c_str(), &_width, &_height, &_bitsPerPixel, 4); // 4 = RGBA

    _textureId = proxies::opengl::Texture::Generate(true);
    Bind();

    proxies::opengl::Texture::SetMinificationFilter(proxies::opengl::enumerators::TargetTexture::Texture2D, proxies::opengl::enumerators::MinificationFilterValue::Linear);
    proxies::opengl::Texture::SetMagnificationFilter(proxies::opengl::enumerators::TargetTexture::Texture2D, proxies::opengl::enumerators::MagnificationFilterValue::Linear);
    proxies::opengl::Texture::SetWrapModeS(proxies::opengl::enumerators::TargetTexture::Texture2D, proxies::opengl::enumerators::TextureWrapMode::ClampToEdge);
    proxies::opengl::Texture::SetWrapModeT(proxies::opengl::enumerators::TargetTexture::Texture2D, proxies::opengl::enumerators::TextureWrapMode::ClampToEdge);

    proxies::opengl::Texture::SendData(proxies::opengl::enumerators::TargetTexture::Texture2D, _width, _height, _data, true);

    Unbind();

    if (_data)
    {
        stbi_image_free(_data);
    }
    else 
    {
        throw std::exception("Image data not loaded");
    }
}

Texture::~Texture()
{
    proxies::opengl::Texture::Delete(_textureId, true);
}

void Texture::Bind(unsigned int slot)
{
    proxies::opengl::Texture::ActivateSlot(slot);
    proxies::opengl::Texture::Bind(proxies::opengl::enumerators::TargetTexture::Texture2D, _textureId, true);
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
