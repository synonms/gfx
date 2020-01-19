#include "texture.h"

#include <GL\glew.h>

#include <utility>

using namespace synonms::gfx::api::opengl;
using namespace synonms::gfx::api::opengl::enumerators;

Texture::Texture(TargetTexture targetTexture)
    : _targetTexture(targetTexture)
{
    glGenTextures(1, &_textureId);
}

Texture::Texture(Texture&& other) noexcept
    : _targetTexture(std::exchange(other._targetTexture, TargetTexture::None))
    , _textureId(std::exchange(other._textureId, 0))
{
}

Texture& Texture::operator=(Texture&& other) noexcept
{
    _targetTexture = std::exchange(other._targetTexture, TargetTexture::None);
    _textureId = std::exchange(other._textureId, 0);

    return *this;
}

Texture::~Texture()
{
    if (_textureId > 0) {
        glDeleteTextures(1, &_textureId);
    }
}


void Texture::Bind() const
{
    glBindTexture(static_cast<unsigned int>(_targetTexture), _textureId);
}

void Texture::SendData(TextureInternalFormat internalFormat, int width, int height, TextureFormat format, DataType dataType, unsigned char* data) const
{
    glTexImage2D(static_cast<unsigned int>(_targetTexture), 0, static_cast<unsigned int>(internalFormat), width, height, 0, static_cast<unsigned int>(format), static_cast<unsigned int>(dataType), data);
}

void Texture::SendCubeMapDataRight(TextureInternalFormat internalFormat, int width, int height, TextureFormat format, DataType dataType, unsigned char* data) const
{
    glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X, 0, static_cast<unsigned int>(internalFormat), width, height, 0, static_cast<unsigned int>(format), static_cast<unsigned int>(dataType), data);
}

void Texture::SendCubeMapDataLeft(TextureInternalFormat internalFormat, int width, int height, TextureFormat format, DataType dataType, unsigned char* data) const
{
    glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_X, 0, static_cast<unsigned int>(internalFormat), width, height, 0, static_cast<unsigned int>(format), static_cast<unsigned int>(dataType), data);
}

void Texture::SendCubeMapDataTop(TextureInternalFormat internalFormat, int width, int height, TextureFormat format, DataType dataType, unsigned char* data) const
{
    glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Y, 0, static_cast<unsigned int>(internalFormat), width, height, 0, static_cast<unsigned int>(format), static_cast<unsigned int>(dataType), data);
}

void Texture::SendCubeMapDataBottom(TextureInternalFormat internalFormat, int width, int height, TextureFormat format, DataType dataType, unsigned char* data) const
{
    glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Y, 0, static_cast<unsigned int>(internalFormat), width, height, 0, static_cast<unsigned int>(format), static_cast<unsigned int>(dataType), data);
}

void Texture::SendCubeMapDataBack(TextureInternalFormat internalFormat, int width, int height, TextureFormat format, DataType dataType, unsigned char* data) const
{
    glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Z, 0, static_cast<unsigned int>(internalFormat), width, height, 0, static_cast<unsigned int>(format), static_cast<unsigned int>(dataType), data);
}

void Texture::SendCubeMapDataFront(TextureInternalFormat internalFormat, int width, int height, TextureFormat format, DataType dataType, unsigned char* data) const
{
    glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Z, 0, static_cast<unsigned int>(internalFormat), width, height, 0, static_cast<unsigned int>(format), static_cast<unsigned int>(dataType), data);
}


void Texture::ActivateSlot(unsigned int slot)
{
    glActiveTexture(GL_TEXTURE0 + slot);
}

void Texture::SetBorderColour(enumerators::TargetTexture targetTexture, const float* rgba)
{
    glTexParameterfv(static_cast<unsigned int>(targetTexture), GL_TEXTURE_BORDER_COLOR, rgba);
}

void Texture::SetCompareFunc(TargetTexture targetTexture, TextureCompareFunc compareFunc)
{
    glTexParameteri(static_cast<unsigned int>(targetTexture), GL_TEXTURE_COMPARE_FUNC, static_cast<int>(compareFunc));
}

void Texture::SetCompareMode(TargetTexture targetTexture, TextureCompareMode compareMode)
{
    glTexParameteri(static_cast<unsigned int>(targetTexture), GL_TEXTURE_COMPARE_MODE, static_cast<int>(compareMode));
}

void Texture::SetMinificationFilter(TargetTexture targetTexture, MinificationFilterValue filterValue)
{
    glTexParameteri(static_cast<unsigned int>(targetTexture), GL_TEXTURE_MIN_FILTER, static_cast<int>(filterValue));
}

void Texture::SetMagnificationFilter(TargetTexture targetTexture, MagnificationFilterValue filterValue)
{
    glTexParameteri(static_cast<unsigned int>(targetTexture), GL_TEXTURE_MAG_FILTER, static_cast<int>(filterValue));
}

void Texture::SetWrapModeR(TargetTexture targetTexture, TextureWrapMode wrapMode)
{
    glTexParameteri(static_cast<unsigned int>(targetTexture), GL_TEXTURE_WRAP_R, static_cast<int>(wrapMode));
}

void Texture::SetWrapModeS(TargetTexture targetTexture, TextureWrapMode wrapMode)
{
    glTexParameteri(static_cast<unsigned int>(targetTexture), GL_TEXTURE_WRAP_S, static_cast<int>(wrapMode));
}

void Texture::SetWrapModeT(TargetTexture targetTexture, TextureWrapMode wrapMode)
{
    glTexParameteri(static_cast<unsigned int>(targetTexture), GL_TEXTURE_WRAP_T, static_cast<int>(wrapMode));
}

void Texture::Unbind(enumerators::TargetTexture targetTexture)
{
    glBindTexture(static_cast<unsigned int>(targetTexture), 0);
}
