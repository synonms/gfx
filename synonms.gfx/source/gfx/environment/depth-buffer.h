#pragma once

namespace synonms
{
    namespace gfx
    {
        namespace environment
        {
            class DepthBuffer
            {
            public:
                DepthBuffer(int width, int height);
                DepthBuffer(DepthBuffer&& other) noexcept;
                DepthBuffer& operator=(DepthBuffer&& other) noexcept;
                ~DepthBuffer();

                DepthBuffer() = delete;
                DepthBuffer(const DepthBuffer& other) = delete;
                DepthBuffer& operator=(const DepthBuffer& other) = delete;

                void Bind() const;
                bool IsReady() const;

            private:
                unsigned int _framebufferId;
                unsigned int _textureId;
            };
        }
    }
}
