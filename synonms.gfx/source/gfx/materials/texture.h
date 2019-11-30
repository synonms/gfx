#pragma once

#include <gfx\enumerators\texture-slot.h>

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
                Texture(Texture&& other) noexcept;
                Texture& operator=(Texture&& other) noexcept;
                ~Texture();

                Texture() = delete;
                Texture(const Texture& other) = delete;
                Texture& operator=(const Texture& other) = delete;

                void Bind(enumerators::TextureSlot slot = enumerators::TextureSlot::Colour) const;
                int GetHeight() const;
                int GetWidth() const;

            public:
                static void Unbind();

            private:
                unsigned int _textureId{ 0 };
                std::string _filePath{ "" };
                int _width{ 0 };
                int _height{ 0 };
                int _bitsPerPixel{ 0 };
            };
        }
    }
}