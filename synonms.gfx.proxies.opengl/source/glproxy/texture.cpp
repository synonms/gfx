#include "texture.h"

#include <glproxy\error.h>

#include <GL\glew.h>

using namespace synonms::gfx::proxies::opengl;
using namespace synonms::gfx::proxies::opengl::enumerators;

void Texture::ActivateSlot(unsigned int slot, bool throwOnError)
{
    if (throwOnError) Error::Clear();

    glActiveTexture(GL_TEXTURE0 + slot);

    if (throwOnError) Error::ThrowIf({
        {GL_INVALID_ENUM, "Slot is outside of acceptabble range." }
        });
}

void Texture::Bind(TargetTexture targetTexture, unsigned int textureId, bool throwOnError)
{
    if (throwOnError) Error::Clear();

    glBindTexture(static_cast<unsigned int>(targetTexture), textureId);

    if (throwOnError) Error::ThrowIf({
        {GL_INVALID_ENUM, "Target is not one of the allowable values." },
        {GL_INVALID_VALUE, "TextureId is not a name returned from a previous call to glGenTextures." },
        {GL_INVALID_OPERATION , "TextureId was previously created with a different target."}
        });
}

void Texture::Delete(unsigned int textureId, bool throwOnError)
{
    if (throwOnError) Error::Clear();

    glDeleteTextures(1, &textureId);

    if (throwOnError) Error::ThrowIf({
        {GL_INVALID_VALUE, "Count is negative." }
    });
}

unsigned int Texture::Generate(bool throwOnError)
{
    if (throwOnError) Error::Clear();

    unsigned int textureId;
    glGenTextures(1, &textureId);

    if (throwOnError) Error::ThrowIf({
        {GL_INVALID_VALUE, "Count is negative." }
        });

    return textureId;
}

void Texture::SendData(TargetTexture targetTexture, TextureInternalFormat internalFormat, int width, int height, TextureFormat format, DataType dataType, unsigned char* data, bool throwOnError)
{
    if (throwOnError) Error::Clear();

    glTexImage2D(static_cast<unsigned int>(targetTexture), 0, static_cast<unsigned int>(internalFormat), width, height, 0, static_cast<unsigned int>(format), static_cast<unsigned int>(dataType), data);

    if (throwOnError) Error::ThrowIf({
        {GL_INVALID_ENUM, "Invalid enum in call to glTexImage2D." },
        {GL_INVALID_VALUE, "Invalid value in call to glTexImage2D." },
        {GL_INVALID_OPERATION, "Invalid operation in call to glTexImage2D." },
        });
}

void Texture::SetCompareFunc(TargetTexture targetTexture, TextureCompareFunc compareFunc, bool throwOnError)
{
    if (throwOnError) Error::Clear();

    glTexParameteri(static_cast<unsigned int>(targetTexture), GL_TEXTURE_COMPARE_FUNC, static_cast<int>(compareFunc));

    if (throwOnError) Error::ThrowIf({
        {GL_INVALID_ENUM, "TargetTexture or FilterValue are invalid." }
        });
}

void Texture::SetCompareMode(TargetTexture targetTexture, TextureCompareMode compareMode, bool throwOnError)
{
    if (throwOnError) Error::Clear();

    glTexParameteri(static_cast<unsigned int>(targetTexture), GL_TEXTURE_COMPARE_MODE, static_cast<int>(compareMode));

    if (throwOnError) Error::ThrowIf({
        {GL_INVALID_ENUM, "TargetTexture or FilterValue are invalid." }
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

void Texture::Unbind(enumerators::TargetTexture targetTexture, bool throwOnError)
{
    if (throwOnError) Error::Clear();

    glBindTexture(static_cast<unsigned int>(targetTexture), 0);

    if (throwOnError) Error::ThrowIf({
        {GL_INVALID_ENUM, "Target is not one of the allowable values." }
        });
}
