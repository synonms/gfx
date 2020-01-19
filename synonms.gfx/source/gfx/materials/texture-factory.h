#pragma once

#include <gfx\io\image.h>

#include <opengl\texture.h>

#include <memory>

namespace synonms
{
    namespace gfx
    {
        namespace materials
        {
            class TextureFactory
            {
            public:
                static std::shared_ptr<api::opengl::Texture> CreateColour(const io::Image& front, const io::Image& back, const io::Image& left, const io::Image& right, const io::Image& top, const io::Image& bottom);
                static std::shared_ptr<api::opengl::Texture> CreateColour(const io::Image& image);
                static std::shared_ptr<api::opengl::Texture> CreateColour(int width, int height,
                    unsigned char* data = nullptr, 
                    api::opengl::enumerators::TextureInternalFormat internalFormat = api::opengl::enumerators::TextureInternalFormat::RGB8, 
                    api::opengl::enumerators::TextureFormat format = api::opengl::enumerators::TextureFormat::RGBA,
                    api::opengl::enumerators::DataType dataType = api::opengl::enumerators::DataType::UnsignedByte);
                static std::shared_ptr<api::opengl::Texture> CreateDepth(int width, int height, unsigned char* data = nullptr);
                static std::shared_ptr<api::opengl::Texture> CreateGBufferPosition(int width, int height);
                static std::shared_ptr<api::opengl::Texture> CreateGBufferNormal(int width, int height);
                static std::shared_ptr<api::opengl::Texture> CreateGBufferAlbedoWithSpecular(int width, int height);
            };
        }
    }
}
