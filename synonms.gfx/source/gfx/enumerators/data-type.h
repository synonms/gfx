#pragma once

namespace synonms
{
    namespace gfx
    {
        namespace enumerators
        {
            enum class DataType : unsigned int
            {
                Byte,
                UnsignedByte,
                Short,
                UnsignedShort,
                Int,
                UnsignedInt,
                Float,
                Double
            };

            class DataTypeMapper
            {
            public:
                static unsigned int ConvertForProxy(DataType dataType);
            };
        }
    }
}

