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
                    enum class TextureWrapMode : unsigned int
                    {
                        ClampToEdge = 0x812F,
                        ClampToBorder = 0x812D,
                        MirroredRepeat = 0x8370,
                        Repeat = 0x2901
                    };
                }
            }
        }
    }
}

