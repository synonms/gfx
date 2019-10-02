#include "data-type.h"

#include <glproxy\enumerators\data-type.h>

using namespace synonms::gfx::enumerators;

unsigned int DataTypeMapper::ConvertForProxy(DataType dataType)
{
    switch (dataType)
    {
        case DataType::Byte: return static_cast<unsigned int>(proxies::opengl::enumerators::DataType::Byte);
        case DataType::UnsignedByte: return static_cast<unsigned int>(proxies::opengl::enumerators::DataType::UnsignedByte);
        case DataType::Short: return static_cast<unsigned int>(proxies::opengl::enumerators::DataType::Short);
        case DataType::UnsignedShort: return static_cast<unsigned int>(proxies::opengl::enumerators::DataType::UnsignedShort);
        case DataType::Int: return static_cast<unsigned int>(proxies::opengl::enumerators::DataType::Int);
        case DataType::UnsignedInt: return static_cast<unsigned int>(proxies::opengl::enumerators::DataType::UnsignedInt);
        case DataType::Float: return static_cast<unsigned int>(proxies::opengl::enumerators::DataType::Float);
        case DataType::Double: return static_cast<unsigned int>(proxies::opengl::enumerators::DataType::Double);
    }

    return 0;
}
