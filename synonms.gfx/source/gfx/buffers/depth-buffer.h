#pragma once

namespace synonms
{
    namespace gfx
    {
        namespace buffers
        {
            class DepthBuffer
            {
            public:
                DepthBuffer(int width = 1024, int height = 1024);
                DepthBuffer(DepthBuffer&& other) noexcept;
                DepthBuffer& operator=(DepthBuffer&& other) noexcept;
                ~DepthBuffer();

                DepthBuffer() = delete;
                DepthBuffer(const DepthBuffer& other) = delete;
                DepthBuffer& operator=(const DepthBuffer& other) = delete;

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
