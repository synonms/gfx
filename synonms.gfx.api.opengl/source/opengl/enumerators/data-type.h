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
                    enum class DataType : unsigned int
                    {
                        Byte = 0x1400,
                        UnsignedByte = 0x1401,
                        Short = 0x1402,
                        UnsignedShort = 0x1403,
                        Int = 0x1404,
                        UnsignedInt = 0x1405,
                        Float = 0x1406,
                        Double = 0x140A,
                        UnsignedInt_24_8 = 0x84FA,
                        UnsignedShort_5_5_5_1 = 0x8034,
                        UnsignedShort_5_6_5 = 0x8363
                    };
                }
            }
        }
    }
}

