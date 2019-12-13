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
                    enum class TextureInternalFormat : unsigned int
                    {
                        // Unsized                  // Corresponding TextureFormat  Corresponding DataType
                        RGB = 0x1907,               // RGB                          UnsignedByte
                        RGBA = 0x1908,              // RGBA                         UnsignedByte
                        LuminanceAlpha = 0x190A,    // LuminanceAlpha               UnsignedByte
                        Luminance = 0x1909,         // Luminance                    UnsignedByte
                        Alpha = 0x1906,             // Alpha                        UnsignedByte

                        // Sized                    // Corresponding TextureFormat  Corresponding DataType
                        R8 = 0x8229,                // Red                          UnsignedByte
                        R8SNorm = 0x8F94,           // Red                          Byte
                        R16F = 0x822D,              // Red                          HalfFloat / Float
                        R32F = 0x822E,              // Red                          Float
                        R8UI = 0x8232,              // RedInteger                   UnsignedByte
                        R8I = 0x8231,               // RedInteger                   Byte
                        R16UI = 0x8234,             // RedInteger                   UnsignedShort
                        R16I = 0x8233,              // RedInteger                   Short
                        R32UI = 0x8236,             // RedInteger                   UnsignedInt
                        R32I = 0x8235,              // RedInteger                   Int

                        RGB8 = 0x8051,              // RGB                          UnsignedByte
                        SRGB8 = 0x8C41,             // RGB                          UnsignedByte
                        RGB565 = 0x8D62,            // RGB                          UnsignedByte / UnsignedShort565
                        RGB8SNorm = 0x8F96,         // RGB                          Byte
                        RGB16F = 0x881B,            // RGB                          HalfFloat / Float
                        RGB32F = 0x8815,            // RGB                          Float
                        RGB8UI = 0x8D7D,            // RGB                          UnsignedByte
                        RGB8I = 0x8D8F,             // RGB                          Byte
                        RGB16UI = 0x8D77,           // RGB                          UnsignedShort
                        RGB16I = 0x8D89,            // RGB                          Short
                        RGB32UI = 0x8D71,           // RGB                          UnsignedInt
                        RGB32I = 0x8D83,            // RGB                          Int

                        RGBA8 = 0x8058,             // RGBA                         UnsignedByte
                        RGBA8SNorm = 0x8F97,        // RGBA                         Byte
                        RGB5_A1 = 0x8057,           // RGBA                         UnsignedByte / UnsignedShort5551
                        RGBA16F = 0x881A,           // RGBA                         HalfFloat / Float
                        RGBA32F = 0x8814,           // RGBA                         Float

                        RGBA8UI = 0x8D7C,           // RGBAInteger                  UnsignedByte
                        RGBA8I = 0x8D8E,            // RGBAInteger                  Byte
                        RGBA16UI = 0x8D76,          // RGBAInteger                  UnsignedShort
                        RGBA16I = 0x8D88,           // RGBAInteger                  Short
                        RGBA32I = 0x8D82,           // RGBAInteger                  Int
                        RGBA32UI = 0x8D70,          // RGBAInteger                  UnsignedInt

                        DepthComponent16 = 0x81A5,  // DepthComponent               UnsignedShort / UnsignedInt
                        DepthComponent24 = 0x81A6,  // DepthComponent               UnsignedInt
                        DepthComponent32F = 0x8CAC, // DepthComponent               Float
                        Depth24Stencil8 = 0x88F0,   // DepthStencil                 UnsignedInt_24_8
                        Depth32FStencil8 = 0x8CAD   // DepthStencil                 Float_32_UnsignedInt_24_8
                    };
                }
            }
        }
    }
}




