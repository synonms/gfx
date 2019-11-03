#pragma once

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
                Texture(const std::string& filePath);
                ~Texture();

                void Bind(unsigned int slot = 0);
                int GetHeight() const;
                int GetWidth() const;
                void Unbind();

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