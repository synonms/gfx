#include "texture-factory.h"

using namespace synonms::gfx::io;
using namespace synonms::gfx::materials;

using namespace synonms::gfx::api::opengl;
using namespace synonms::gfx::api::opengl::enumerators;

std::shared_ptr<Texture> TextureFactory::CreateColour(const Image& front, const Image& back, const Image& left, const Image& right, const Image& top, const Image& bottom)
{
    auto texture = std::make_shared<Texture>(TargetTexture::TextureCubeMap);

    texture->Bind();

    texture->SendCubeMapDataRight(right.GetTextureInternalFormat(), right.GetWidth(), right.GetHeight(), right.GetTextureFormat(), right.GetDataType(), right.GetData());
    texture->SendCubeMapDataLeft(left.GetTextureInternalFormat(), left.GetWidth(), left.GetHeight(), left.GetTextureFormat(), left.GetDataType(), left.GetData());
    texture->SendCubeMapDataTop(top.GetTextureInternalFormat(), top.GetWidth(), top.GetHeight(), top.GetTextureFormat(), top.GetDataType(), top.GetData());
    texture->SendCubeMapDataBottom(bottom.GetTextureInternalFormat(), bottom.GetWidth(), bottom.GetHeight(), bottom.GetTextureFormat(), bottom.GetDataType(), bottom.GetData());
    texture->SendCubeMapDataBack(back.GetTextureInternalFormat(), back.GetWidth(), back.GetHeight(), back.GetTextureFormat(), back.GetDataType(), back.GetData());
    texture->SendCubeMapDataFront(front.GetTextureInternalFormat(), front.GetWidth(), front.GetHeight(), front.GetTextureFormat(), front.GetDataType(), front.GetData());

    Texture::SetMinificationFilter(TargetTexture::TextureCubeMap, MinificationFilterValue::Linear);
    Texture::SetMagnificationFilter(TargetTexture::TextureCubeMap, MagnificationFilterValue::Linear);
    Texture::SetWrapModeR(TargetTexture::TextureCubeMap, TextureWrapMode::ClampToEdge);
    Texture::SetWrapModeS(TargetTexture::TextureCubeMap, TextureWrapMode::ClampToEdge);
    Texture::SetWrapModeT(TargetTexture::TextureCubeMap, TextureWrapMode::ClampToEdge);

    Texture::Unbind(TargetTexture::TextureCubeMap);

    return std::move(texture);
}

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
