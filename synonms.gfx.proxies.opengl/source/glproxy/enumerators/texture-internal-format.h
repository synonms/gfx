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
                    // TODO - Many other options
                    enum class TextureInternalFormat : unsigned int
                    {
                        GL_RGB = 0x1907,
                        GL_RGBA = 0x1908,
                        GL_RGB8 = 0x8051,
                        GL_LUMINANCE_ALPHA = 0x190A,
                        GL_LUMINANCE = 0x1909,
                        GL_ALPHA = 0x1906,
                        GL_DEPTH_COMPONENT16 = 0x81A5,
                        GL_DEPTH_COMPONENT24 = 0x81A6,
                        GL_DEPTH_COMPONENT32F = 0x8CAC,
                        GL_DEPTH24_STENCIL8 = 0x88F0,
                        GL_DEPTH32F_STENCIL8 = 0x8CAD
                    };
                }
            }
        }
    }
}




