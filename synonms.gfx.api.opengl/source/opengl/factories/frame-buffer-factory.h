#pragma once

#include <opengl\frame-buffer.h>

#include <memory>

namespace synonms
{
    namespace gfx
    {
        namespace api
        {
            namespace opengl
            {
                namespace factories
                {
                    class FrameBufferFactory
                    {
                    public:
                        static std::unique_ptr<FrameBuffer> CreateOffscreenBuffer(int width, int height, unsigned int colourTextureId, unsigned int depthStencilRenderBufferId);
                    };
                }
            }
        }
    }
}
