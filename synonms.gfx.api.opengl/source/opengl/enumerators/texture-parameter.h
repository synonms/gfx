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
                    enum class TextureParameter : unsigned int
                    {
                        BaseLevel = 0x813C,
                        CompareFunc = 0x884D,
                        CompareMode = 0x884C,
                        LevelOfDetailBias = 0x8501,
                        MinificationFilter = 0x2801,
                        MagnificationFilter = 0x2800,
                        MinLevelOfDetail = 0x813A,
                        MaxLevelOfDetail = 0x813B,
                        MaxLevel = 0x813D,
                        SwizzleR = 0x8E42,
                        SwizzleG = 0x8E43,
                        SwizzleB = 0x8E44,
                        SwizzleA = 0x8E45,
                        WrapS = 0x2802,
                        WrapT = 0x2803,
                        WrapR = 0x8072
                    };
                }
            }
        }
    }
}
