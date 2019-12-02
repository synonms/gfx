#pragma once

#include <glproxy\enumerators\attachment-point.h>
#include <glproxy\enumerators\data-type.h>
#include <glproxy\enumerators\draw-buffer-mode.h>
#include <glproxy\enumerators\read-buffer-mode.h>
#include <glproxy\enumerators\framebuffer-status.h>
#include <glproxy\enumerators\framebuffer-target.h>
#include <glproxy\enumerators\target-texture.h>
#include <glproxy\enumerators\pixel-read-colour-format.h>

namespace synonms
{
    namespace gfx
    {
        namespace proxies
        {
            namespace opengl
            {
                class FrameBuffer
                {
                public:
                    FrameBuffer();
                    FrameBuffer(FrameBuffer&& other) noexcept;
                    FrameBuffer& operator=(FrameBuffer&& other) noexcept;
                    ~FrameBuffer();

                    FrameBuffer(const FrameBuffer& other) = delete;
                    FrameBuffer& operator=(const FrameBuffer& other) = delete;

                public:
                    void Bind(enumerators::FramebufferTarget target, bool throwOnError = false) const;

                public:
                    static void AttachRenderBuffer(enumerators::FramebufferTarget target, enumerators::AttachmentPoint attachmentPoint, unsigned int renderBufferId, bool throwOnError = false);
                    static void AttachTexture2d(enumerators::FramebufferTarget target, enumerators::AttachmentPoint attachmentPoint, enumerators::TargetTexture targetTexture, unsigned int textureId, bool throwOnError = false);
                    static void BindDefault(enumerators::FramebufferTarget target, bool throwOnError = false);
                    static enumerators::FramebufferStatus GetStatus(enumerators::FramebufferTarget target, bool throwOnError = false);
                    static void ReadColourPixels(int left, int bottom, int width, int height, enumerators::PixelReadColourFormat pixelReadFormat, enumerators::DataType dataType, void* data, bool throwOnError = false);
                    static void ReadDepthPixels(int left, int bottom, int width, int height, enumerators::DataType dataType, void* data, bool throwOnError = false);
                    static void ReadDepthStencilPixels(int left, int bottom, int width, int height, enumerators::DataType dataType, void* data, bool throwOnError = false);
                    static void ReadStencilPixels(int left, int bottom, int width, int height, enumerators::DataType dataType, void* data, bool throwOnError = false);
                    static void SetDrawBuffer(enumerators::DrawBufferMode mode, bool throwOnError = false);
                    static void SetReadBuffer(enumerators::ReadBufferMode mode, bool throwOnError = false);

                private:
                    unsigned int _frameBufferId{ 0 };
                };
            }
        }
    }
}
