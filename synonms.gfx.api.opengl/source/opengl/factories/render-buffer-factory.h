#pragma once

#include <opengl\render-buffer.h>

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
