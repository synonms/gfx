#include "texture.h"

#include <glproxy\error.h>

#include <GL\glew.h>

using namespace synonms::gfx::proxies::opengl;
using namespace synonms::gfx::proxies::opengl::enumerators;

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


void Texture::Bind(bool throwOnError) const
{
    if (throwOnError) Error::Clear();

    glBindTexture(static_cast<unsigned int>(_targetTexture), _textureId);

    if (throwOnError) Error::ThrowIf({
        {GL_INVALID_ENUM, "Target is not one of the allowable values." },
        {GL_INVALID_VALUE, "TextureId is not a name returned from a previous call to glGenTextures." },
        {GL_INVALID_OPERATION , "TextureId was previously created with a different target."}
        });
}

void Texture::SendData(TextureInternalFormat internalFormat, int width, int height, TextureFormat format, DataType dataType, unsigned char* data, bool throwOnError) const
{
    if (throwOnError) Error::Clear();

    glTexImage2D(static_cast<unsigned int>(_targetTexture), 0, static_cast<unsigned int>(internalFormat), width, height, 0, static_cast<unsigned int>(format), static_cast<unsigned int>(dataType), data);

    if (throwOnError) Error::ThrowIf({
        {GL_INVALID_ENUM, "Invalid enum in call to glTexImage2D." },
        {GL_INVALID_VALUE, "Invalid value in call to glTexImage2D." },
        {GL_INVALID_OPERATION, "Invalid operation in call to glTexImage2D." },
        });
}


void Texture::SetBorderColour(enumerators::TargetTexture targetTexture, const float* rgba, bool throwOnError)
{
    if (throwOnError) Error::Clear();

    glTexParameterfv(static_cast<unsigned int>(targetTexture), GL_TEXTURE_BORDER_COLOR, rgba);

    if (throwOnError) Error::ThrowIf({
        {GL_INVALID_ENUM, "TargetTexture is invalid." }
        });
}

void Texture::SetCompareFunc(TargetTexture targetTexture, TextureCompareFunc compareFunc, bool throwOnError)
{
    if (throwOnError) Error::Clear();

    glTexParameteri(static_cast<unsigned int>(targetTexture), GL_TEXTURE_COMPARE_FUNC, static_cast<int>(compareFunc));

    if (throwOnError) Error::ThrowIf({
        {GL_INVALID_ENUM, "TargetTexture or CompareFunc are invalid." }
        });
}

void Texture::SetCompareMode(TargetTexture targetTexture, TextureCompareMode compareMode, bool throwOnError)
{
    if (throwOnError) Error::Clear();

    glTexParameteri(static_cast<unsigned int>(targetTexture), GL_TEXTURE_COMPARE_MODE, static_cast<int>(compareMode));

    if (throwOnError) Error::ThrowIf({
        {GL_INVALID_ENUM, "TargetTexture or CompareMode are invalid." }
        });
}

void Texture::SetMinificationFilter(TargetTexture targetTexture, MinificationFilterValue filterValue, bool throwOnError)
{
    if (throwOnError) Error::Clear();

    glTexParameteri(static_cast<unsigned int>(targetTexture), GL_TEXTURE_MIN_FILTER, static_cast<int>(filterValue));

    if (throwOnError) Error::ThrowIf({
        {GL_INVALID_ENUM, "TargetTexture or FilterValue are invalid." }
        });
}

void Texture::SetMagnificationFilter(TargetTexture targetTexture, MagnificationFilterValue filterValue, bool throwOnError)
{
    if (throwOnError) Error::Clear();

    glTexParameteri(static_cast<unsigned int>(targetTexture), GL_TEXTURE_MAG_FILTER, static_cast<int>(filterValue));

    if (throwOnError) Error::ThrowIf({
        {GL_INVALID_ENUM, "TargetTexture or FilterValue are invalid." }
        });
}

void Texture::SetWrapModeS(TargetTexture targetTexture, TextureWrapMode wrapMode, bool throwOnError)
{
    if (throwOnError) Error::Clear();

    glTexParameteri(static_cast<unsigned int>(targetTexture), GL_TEXTURE_WRAP_S, static_cast<int>(wrapMode));

    if (throwOnError) Error::ThrowIf({
        {GL_INVALID_ENUM, "TargetTexture or WrapMode are invalid." }
        });
}

void Texture::SetWrapModeT(TargetTexture targetTexture, TextureWrapMode wrapMode, bool throwOnError)
{
    if (throwOnError) Error::Clear();

    glTexParameteri(static_cast<unsigned int>(targetTexture), GL_TEXTURE_WRAP_T, static_cast<int>(wrapMode));

    if (throwOnError) Error::ThrowIf({
        {GL_INVALID_ENUM, "TargetTexture or WrapMode are invalid." }
        });
}


void Texture::ActivateSlot(unsigned int slot, bool throwOnError)
{
    if (throwOnError) Error::Clear();

    glActiveTexture(GL_TEXTURE0 + slot);

    if (throwOnError) Error::ThrowIf({
        {GL_INVALID_ENUM, "Slot is outside of acceptabble range." }
        });
}

void Texture::Unbind(enumerators::TargetTexture targetTexture, bool throwOnError)
{
    if (throwOnError) Error::Clear();

    glBindTexture(static_cast<unsigned int>(targetTexture), 0);

    if (throwOnError) Error::ThrowIf({
        {GL_INVALID_ENUM, "Target is not one of the allowable values." }
        });
}
