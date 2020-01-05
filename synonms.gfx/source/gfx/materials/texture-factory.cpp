#include "texture-factory.h"

using namespace synonms::gfx::io;
using namespace synonms::gfx::materials;

using namespace synonms::gfx::api::opengl;
using namespace synonms::gfx::api::opengl::enumerators;

std::shared_ptr<Texture> TextureFactory::CreateColour(const Image& image)
{
    auto texture = std::make_shared<Texture>(TargetTexture::Texture2D);

    texture->Bind();

    texture->SendData(image.GetTextureInternalFormat(), image.GetWidth(), image.GetHeight(), image.GetTextureFormat(), image.GetDataType(), image.GetData());

    Texture::SetMinificationFilter(TargetTexture::Texture2D, MinificationFilterValue::Linear);
    Texture::SetMagnificationFilter(TargetTexture::Texture2D, MagnificationFilterValue::Linear);
    Texture::SetWrapModeS(TargetTexture::Texture2D, TextureWrapMode::ClampToEdge);
    Texture::SetWrapModeT(TargetTexture::Texture2D, TextureWrapMode::ClampToEdge);

    Texture::Unbind(TargetTexture::Texture2D);

    return std::move(texture);
}

std::shared_ptr<Texture> TextureFactory::CreateColour(int width, int height, unsigned char* data, TextureInternalFormat internalFormat, TextureFormat format, DataType dataType)
{
    auto texture = std::make_shared<Texture>(TargetTexture::Texture2D);

    texture->Bind();

    texture->SendData(internalFormat, width, height, format, dataType, data);

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

std::shared_ptr<Texture> TextureFactory::CreateGBufferPosition(int width, int height)
{
    auto texture = std::make_shared<Texture>(TargetTexture::Texture2D);

    texture->Bind();

    texture->SendData(TextureInternalFormat::RGB16F, width, height, TextureFormat::RGB, DataType::Float, nullptr);

    Texture::SetMinificationFilter(TargetTexture::Texture2D, MinificationFilterValue::Nearest);
    Texture::SetMagnificationFilter(TargetTexture::Texture2D, MagnificationFilterValue::Nearest);

    Texture::Unbind(TargetTexture::Texture2D);

    return std::move(texture);
}

std::shared_ptr<Texture> TextureFactory::CreateGBufferNormal(int width, int height)
{
    auto texture = std::make_shared<Texture>(TargetTexture::Texture2D);

    texture->Bind();

    texture->SendData(TextureInternalFormat::RGB16F, width, height, TextureFormat::RGB, DataType::Float, nullptr);

    Texture::SetMinificationFilter(TargetTexture::Texture2D, MinificationFilterValue::Nearest);
    Texture::SetMagnificationFilter(TargetTexture::Texture2D, MagnificationFilterValue::Nearest);

    Texture::Unbind(TargetTexture::Texture2D);

    return std::move(texture);
}

std::shared_ptr<Texture> TextureFactory::CreateGBufferAlbedoWithSpecular(int width, int height)
{
    auto texture = std::make_shared<Texture>(TargetTexture::Texture2D);

    texture->Bind();

    texture->SendData(TextureInternalFormat::RGBA, width, height, TextureFormat::RGBA, DataType::UnsignedByte, nullptr);

    Texture::SetMinificationFilter(TargetTexture::Texture2D, MinificationFilterValue::Nearest);
    Texture::SetMagnificationFilter(TargetTexture::Texture2D, MagnificationFilterValue::Nearest);

    Texture::Unbind(TargetTexture::Texture2D);

    return std::move(texture);
}