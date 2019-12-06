#pragma once

namespace synonms
{
    namespace gfx
    {
        namespace api
        {
            namespace opengl
            {
                namespace enumerators
                {
                    // TODO - Many other options
                    enum class TextureInternalFormat : unsigned int
                    {
                        RGB = 0x1907,
                        RGBA = 0x1908,
                        RGB8 = 0x8051,
                        LuminanceAlpha = 0x190A,
                        Luminance = 0x1909,
                        Alpha = 0x1906,
                        DepthComponent16 = 0x81A5,
                        DepthComponent24 = 0x81A6,
                        DepthComponent32F = 0x8CAC,
                        Depth24Stencil8 = 0x88F0,
                        Depth32FStencil8 = 0x8CAD
                    };
                }
            }
        }
    }
}




