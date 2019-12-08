#include "texture-factory.h"

using namespace synonms::gfx::api::opengl;
using namespace synonms::gfx::api::opengl::enumerators;
using namespace synonms::gfx::api::opengl::factories;

std::shared_ptr<Texture> TextureFactory::CreateColour(int width, int height, unsigned char* data)
{
    auto texture = std::make_shared<Texture>(TargetTexture::Texture2D);

    texture->Bind();

    texture->SendData(
        TextureInternalFormat::RGB8,
        width, height,
        TextureFormat::RGBA,
        DataType::UnsignedByte,
        data);

    Texture::SetMinificationFilter(TargetTexture::Texture2D, MinificationFilterValue::Linear);
    Texture::SetMagnificationFilter(TargetTexture::Texture2D, MagnificationFilterValue::Linear);
    Texture::SetWrapModeS(TargetTexture::Texture2D, TextureWrapMode::ClampToEdge);
    Texture::SetWrapModeT(TargetTexture::Texture2D, TextureWrapMode::ClampToEdge);


    Texture::Unbind(TargetTexture::Texture2D);

    return std::move(texture);
}

std::shared_ptr<Texture> TextureFactory::CreateDepth(int width, int height, unsigned char* data)
{
    auto texture = std::make_shared<Texture>(TargetTexture::Texture2D);

    texture->Bind();

    texture->SendData(
        TextureInternalFormat::DepthComponent32F,
        width, height,
        TextureFormat::DepthComponent,
        DataType::Float,
        data);

    Texture::SetMinificationFilter(TargetTexture::Texture2D, MinificationFilterValue::Linear);
    Texture::SetMagnificationFilter(TargetTexture::Texture2D, MagnificationFilterValue::Linear);
    Texture::SetWrapModeS(TargetTexture::Texture2D, TextureWrapMode::ClampToBorder);
    Texture::SetWrapModeT(TargetTexture::Texture2D, TextureWrapMode::ClampToBorder);
    float borderColour[] = { 1.0f, 1.0f, 1.0f, 1.0f };
    Texture::SetBorderColour(TargetTexture::Texture2D, borderColour);
//    Texture::SetCompareMode(TargetTexture::Texture2D, TextureCompareMode::CompareRefToTexture);
//    Texture::SetCompareFunc(TargetTexture::Texture2D, TextureCompareFunc::LessThanOrEqual);

    Texture::Unbind(TargetTexture::Texture2D);

    return std::move(texture);
}
