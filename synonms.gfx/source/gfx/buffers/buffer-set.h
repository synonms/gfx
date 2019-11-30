#pragma once

#include <gfx\buffers\colour-buffer.h>
#include <gfx\buffers\depth-buffer.h>

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
                BufferSet();
                BufferSet(BufferSet&& other) noexcept;
                BufferSet& operator=(BufferSet&& other) noexcept;
                ~BufferSet();

                BufferSet(const BufferSet& other) = delete;
                BufferSet& operator=(const BufferSet& other) = delete;

                void Bind() const;
                bool IsReady() const;
                void SetColourBuffer(std::shared_ptr<ColourBuffer> buffer, int bufferIndex);
                void SetDepthBuffer(std::shared_ptr<DepthBuffer> buffer);
                void Unbind() const;

            private:
                unsigned int _framebufferId;
                std::shared_ptr<DepthBuffer> _depthBuffer;
                std::map<int, std::shared_ptr<ColourBuffer>> _colourBuffers;
            };
        }
    }
}
