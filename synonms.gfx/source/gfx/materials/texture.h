#pragma once

#include <gfx\exports.h>

#include <string>

namespace synonms
{
    namespace gfx
    {
        namespace materials
        {
            class Texture
            {
            public:
                SYNONMS_GFX_API Texture(const std::string& filePath);
                SYNONMS_GFX_API ~Texture();

                SYNONMS_GFX_API void Bind(unsigned int slot = 0);
                SYNONMS_GFX_API int GetHeight() const;
                SYNONMS_GFX_API int GetWidth() const;
                SYNONMS_GFX_API void Unbind();

            private:
                unsigned int _textureId{ 0 };
                std::string _filePath{ "" };
                unsigned char* _data{ nullptr };
                int _width{ 0 };
                int _height{ 0 };
                int _bitsPerPixel{ 0 };
            };
        }
    }
}