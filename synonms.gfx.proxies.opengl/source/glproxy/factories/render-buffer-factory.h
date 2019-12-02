#pragma once

#include <glproxy\render-buffer.h>

#include <memory>

namespace synonms
{
    namespace gfx
    {
        namespace proxies
        {
            namespace opengl
            {
                namespace factories
                {
                    class RenderBufferFactory
                    {
                    public:
                        static std::unique_ptr<RenderBuffer> CreateDepthStencilBuffer(int width, int height);
                    };
                }
            }
        }
    }
}
