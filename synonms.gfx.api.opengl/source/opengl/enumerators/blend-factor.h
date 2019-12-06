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
                    enum class BlendFactor : unsigned int
                    {
                        Zero = 0,
                        One = 1,
                        SourceColour = 0x0300,
                        OneMinusSourceColour = 0x0301,
                        DestinationColour = 0x0306,
                        OneMinusDestinationColour = 0x0307,
                        SourceAlpha = 0x0302,
                        OneMinusSourceAlpha = 0x0303,
                        DestinationAlpha = 0x0304,
                        OneMinusDestinationAlpha = 0x0305,
                        ConstantColour = 0x8001,
                        OneMinusConstantColour = 0x8002,
                        ConstantAlpha = 0x8003,
                        OneMinusConstantAlpha = 0x8004
                    };
                }
            }
        }
    }
}




