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
                        static std::unique_ptr<FrameBuffer> CreateShadowmapBuffer(int width, int height, unsigned int depthTextureId, unsigned int colourTextureId = 0);
                        static std::unique_ptr<FrameBuffer> CreateGBuffer(int width, int height, unsigned int positionTextureId, unsigned int normalTextureId, unsigned int albedoSpecularTextureId, unsigned int depthStencilRenderBufferId);
                    };
                }
            }
        }
    }
}
