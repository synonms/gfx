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
                    enum class AttributeBit : unsigned int
                    {
                        Current = 0x00000001,
                        Point = 0x00000002,
                        Line = 0x00000004,
                        Polygon = 0x00000008,
                        PolygonStipple = 0x00000010,
                        PixelMode = 0x00000020,
                        Lighting = 0x00000040,
                        Fog = 0x00000080,
                        DepthBuffer = 0x00000100,
                        AccumBuffer = 0x00000200,
                        StencilBuffer = 0x00000400,
                        Viewport = 0x00000800,
                        Transform = 0x00001000,
                        Enable = 0x00002000,
                        ColourBuffer = 0x00004000,
                        Hint = 0x00008000,
                        Eval = 0x00010000,
                        List = 0x00020000,
                        Texture = 0x00040000,
                        Scissor = 0x00080000,
                        AllAttributes = 0x000fffff
                    };

                    inline AttributeBit operator |(AttributeBit lhs, AttributeBit rhs)
                    {
                        return static_cast<AttributeBit>(
                            static_cast<unsigned int>(lhs) | static_cast<unsigned int>(rhs)
                            );
                    }
                }
            }
        }
    }
}
