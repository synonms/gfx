#pragma once

namespace synonms
{
    namespace gfx
    {
        namespace buffers
        {
            class ColourBuffer
            {
            public:
                ColourBuffer(int width = 1024, int height = 1024);
                ColourBuffer(ColourBuffer&& other) noexcept;
                ColourBuffer& operator=(ColourBuffer&& other) noexcept;
                ~ColourBuffer();

                ColourBuffer() = delete;
                ColourBuffer(const ColourBuffer& other) = delete;
                ColourBuffer& operator=(const ColourBuffer& other) = delete;

                void Bind() const;

                inline int GetWidth() const { return _width; }
                inline int GetHeight() const { return _height; }
                inline int GetTextureId() const { return _textureId; }

            private:
                int _width;
                int _height;
                unsigned int _textureId;
            };
        }
    }
}
