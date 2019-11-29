#pragma once

namespace synonms
{
    namespace gfx
    {
        namespace proxies
        {
            namespace opengl
            {
                namespace enumerators
                {
                    enum class FramebufferStatus : unsigned int
                    {
                        GL_FRAMEBUFFER_COMPLETE = 0x8CD5,
                        GL_FRAMEBUFFER_UNDEFINED,
                        GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT = 0x8CD6,
                        GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT = 0x8CD7,
                        GL_FRAMEBUFFER_INCOMPLETE_DRAW_BUFFER = 0x8CDB,
                        GL_FRAMEBUFFER_INCOMPLETE_READ_BUFFER = 0x8CDC,
                        GL_FRAMEBUFFER_UNSUPPORTED = 0x8CDD,
                        GL_FRAMEBUFFER_INCOMPLETE_MULTISAMPLE = 0x8D56,
                        GL_FRAMEBUFFER_INCOMPLETE_LAYER_TARGETS = 0x8DA8
                    };
                }
            }
        }
    }
}




