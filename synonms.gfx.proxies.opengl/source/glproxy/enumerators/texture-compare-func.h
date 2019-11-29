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
                    enum class TextureCompareFunc : unsigned int
                    {
                        LessThanOrEqual = 0x0203,
                        GreaterThanOrEqual = 0x0206,
                        LessThan = 0x0201,
                        GreaterThan = 0x0204,
                        Equal = 0x0202,
                        NotEqual = 0x0205,
                        Always = 0x0207,
                        Never = 0x0200
                    };
                }
            }
        }
    }
}
