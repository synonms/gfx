#pragma once

#include <opengl\enumerators\attachment-point.h>
#include <opengl\enumerators\attribute-bit.h>
#include <opengl\enumerators\data-type.h>
#include <opengl\enumerators\draw-buffer-mode.h>
#include <opengl\enumerators\framebuffer-status.h>
#include <opengl\enumerators\framebuffer-target.h>
#include <opengl\enumerators\pixel-read-colour-format.h>
#include <opengl\enumerators\read-buffer-mode.h>
#include <opengl\enumerators\target-texture.h>

namespace synonms
{
    namespace gfx
    {
        namespace api
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
                    void Bind(enumerators::FramebufferTarget target) const;
                    inline unsigned int GetFrameBufferId() const { return _frameBufferId; }

                public:
                    static void AttachRenderBuffer(enumerators::FramebufferTarget target, enumerators::AttachmentPoint attachmentPoint, unsigned int renderBufferId);
                    static void AttachTexture2d(enumerators::FramebufferTarget target, enumerators::AttachmentPoint attachmentPoint, enumerators::TargetTexture targetTexture, unsigned int textureId);
                    static void BindDefault(enumerators::FramebufferTarget target);
                    static void Clear(enumerators::AttributeBit attributeBit = enumerators::AttributeBit::ColourBuffer);
                    static void ClearColour(float red, float green, float blue, float alpha);
                    static void ClearDepth(double value);
                    static void ClearStencil(int value);
                    static enumerators::FramebufferStatus GetStatus(enumerators::FramebufferTarget target);
                    static void ReadColourPixels(int left, int bottom, int width, int height, enumerators::PixelReadColourFormat pixelReadFormat, enumerators::DataType dataType, void* data);
                    static void ReadDepthPixels(int left, int bottom, int width, int height, enumerators::DataType dataType, void* data);
                    static void ReadDepthStencilPixels(int left, int bottom, int width, int height, enumerators::DataType dataType, void* data);
                    static void ReadStencilPixels(int left, int bottom, int width, int height, enumerators::DataType dataType, void* data);
                    static void SetDrawBuffer(enumerators::DrawBufferMode mode);
                    static void SetReadBuffer(enumerators::ReadBufferMode mode);

                private:
                    unsigned int _frameBufferId{ 0 };
                };
            }
        }
    }
}
