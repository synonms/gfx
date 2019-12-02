#pragma once

#include <glproxy\frame-buffer.h>
#include <glproxy\render-buffer.h>
#include <glproxy\texture.h>

#include <map>
#include <memory>

namespace synonms
{
    namespace gfx
    {
        namespace buffers
        {
            class BufferSet
            {
            public:
                BufferSet(int width, int height);
                BufferSet(BufferSet&& other) noexcept;
                BufferSet& operator=(BufferSet&& other) noexcept;
                ~BufferSet();

                BufferSet() = delete;
                BufferSet(const BufferSet& other) = delete;
                BufferSet& operator=(const BufferSet& other) = delete;

                void Bind() const;

                inline const proxies::opengl::Texture* const GetColourTexture(int index) const { return _colourTextures.find(index) != std::end(_colourTextures) ? _colourTextures.at(index).get() : nullptr; }

            private:
                std::unique_ptr<proxies::opengl::FrameBuffer> _frameBuffer{ nullptr };
                std::unique_ptr<proxies::opengl::RenderBuffer> _depthStencilBuffer{ nullptr };
                std::map<int, std::shared_ptr<proxies::opengl::Texture>> _colourTextures;
            };
        }
    }
}
