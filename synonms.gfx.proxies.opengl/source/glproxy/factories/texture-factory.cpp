#include "texture-factory.h"

using namespace synonms::gfx::proxies::opengl;
using namespace synonms::gfx::proxies::opengl::enumerators;
using namespace synonms::gfx::proxies::opengl::factories;

std::shared_ptr<Texture> TextureFactory::CreateColour(int width, int height, unsigned char* data)
{
    auto texture = std::make_shared<Texture>(TargetTexture::Texture2D);

    texture->Bind();

    texture->SendData(
        TextureInternalFormat::GL_RGB8,
        width, height,
        TextureFormat::GL_RGBA,
        DataType::UnsignedByte,
        data, true);

    Texture::SetMinificationFilter(TargetTexture::Texture2D, MinificationFilterValue::Linear);
    Texture::SetMagnificationFilter(TargetTexture::Texture2D, MagnificationFilterValue::Linear);
//    Texture::SetWrapModeS(TargetTexture::Texture2D, TextureWrapMode::ClampToEdge);
//    Texture::SetWrapModeT(TargetTexture::Texture2D, TextureWrapMode::ClampToEdge);


    Texture::Unbind(TargetTexture::Texture2D);

    return std::move(texture);
}

std::shared_ptr<Texture> TextureFactory::CreateDepth(int width, int height, unsigned char* data)
{
    auto texture = std::make_shared<Texture>(TargetTexture::Texture2D);

    texture->Bind();

    Texture::SetMinificationFilter(TargetTexture::Texture2D, MinificationFilterValue::Linear);
    Texture::SetMagnificationFilter(TargetTexture::Texture2D, MagnificationFilterValue::Linear);
    Texture::SetWrapModeS(TargetTexture::Texture2D, TextureWrapMode::ClampToEdge);
    Texture::SetWrapModeT(TargetTexture::Texture2D, TextureWrapMode::ClampToEdge);
    Texture::SetCompareMode(TargetTexture::Texture2D, TextureCompareMode::CompareRefToTexture);
    Texture::SetCompareFunc(TargetTexture::Texture2D, TextureCompareFunc::LessThanOrEqual);

    texture->SendData(
        TextureInternalFormat::GL_DEPTH_COMPONENT32F,
        width, height,
        TextureFormat::GL_DEPTH_COMPONENT,
        DataType::Float,
        data, true);

    Texture::Unbind(TargetTexture::Texture2D);

    return std::move(texture);
}
