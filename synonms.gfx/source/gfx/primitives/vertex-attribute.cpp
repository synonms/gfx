#include "vertex-attribute.h"

#include <glproxy\enumerators\data-type.h>

using namespace synonms::gfx::enumerators;
using namespace synonms::gfx::primitives;

VertexAttribute::VertexAttribute(AttributeType attributeType, DataType dataType, int noOfComponents, int noOfBytesPerComponent, bool isNormalised)
    : _attributeType(attributeType)
    , _dataType(dataType)
    , _noOfComponents(noOfComponents)
    , _noOfBytes(noOfComponents * noOfBytesPerComponent)
    , _isNormalised(isNormalised)
{
}

AttributeType VertexAttribute::GetAttributeType() const
{
    return _attributeType;
}

DataType VertexAttribute::GetDataType() const
{
    return _dataType;
}

bool VertexAttribute::GetIsNormalised() const
{
    return _isNormalised;
}

int VertexAttribute::GetNoOfBytes() const
{
    return _noOfBytes;
}

int VertexAttribute::GetNoOfComponents() const
{
    return _noOfComponents;
}
