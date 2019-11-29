#pragma once

#include <glproxy\enumerators\attachment-point.h>
#include <glproxy\enumerators\draw-buffer-mode.h>
#include <glproxy\enumerators\read-buffer-mode.h>
#include <glproxy\enumerators\framebuffer-status.h>
#include <glproxy\enumerators\framebuffer-target.h>
#include <glproxy\enumerators\target-texture.h>

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
                    static void AttachTexture2d(enumerators::FramebufferTarget target, enumerators::AttachmentPoint attachmentPoint, enumerators::TargetTexture targetTexture, unsigned int textureId, bool throwOnError = false);
                    static void Bind(enumerators::FramebufferTarget target, unsigned int framebufferId, bool throwOnError = false);
                    static void Delete(unsigned int framebufferId, bool throwOnError = false);
                    static unsigned int Generate(bool throwOnError = false);
                    static enumerators::FramebufferStatus GetStatus(enumerators::FramebufferTarget target, bool throwOnError = false);
                    static void SetDrawBuffer(enumerators::DrawBufferMode mode, bool throwOnError = false);
                    static void SetReadBuffer(enumerators::ReadBufferMode mode, bool throwOnError = false);
                };
            }
        }
    }
}
