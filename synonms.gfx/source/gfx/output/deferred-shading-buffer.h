#pragma once

#include <opengl\frame-buffer.h>

#include <memory>

namespace synonms
{
    namespace gfx
    {
        namespace output
        {
            class DeferredShadingBuffer
            {
            public:
                DeferredShadingBuffer();


            private:
                std::unique_ptr<api::opengl::FrameBuffer> _frameBuffer{ nullptr };
            };
        }
    }
}