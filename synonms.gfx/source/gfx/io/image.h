#pragma once

#include <string>

#include <opengl\enumerators\data-type.h>
#include <opengl\enumerators\texture-format.h>
#include <opengl\enumerators\texture-internal-format.h>

namespace synonms
{
    namespace gfx
    {
        namespace io
        {
            class Image
            {
            public:
                Image(const std::string& filePath);
                Image(Image&& other) noexcept;
                Image& operator=(Image&& other) noexcept;
                ~Image();

                Image() = delete;
                Image(const Image& other) = delete;
                Image& operator=(const Image& other) = delete;

                inline unsigned int GetBitsPerPixel() const { return _bitsPerPixel; }
                inline unsigned char* GetData() const { return _data; }
                inline unsigned int GetHeight() const { return _height; }
                inline unsigned int GetWidth() const { return _width; }

                api::opengl::enumerators::DataType GetDataType() const;
                api::opengl::enumerators::TextureFormat GetTextureFormat() const;
                api::opengl::enumerators::TextureInternalFormat GetTextureInternalFormat() const;

            private:
                void* _imageData{ nullptr };
                unsigned char* _data{ nullptr };
                int _imageType{ 0 };
                unsigned int _width{ 0 };
                unsigned int _height{ 0 };
                unsigned int _bitsPerPixel{ 0 };
                unsigned int _redMask{ 0 };
                unsigned int _greenMask{ 0 };
                unsigned int _blueMask{ 0 };
                std::string error{ "" };
            };
        }
    }
}
