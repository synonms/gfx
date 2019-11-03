#pragma once

#include <gfx\enumerators\attribute-type.h>
#include <gfx\enumerators\data-type.h>

namespace synonms
{
    namespace gfx
    {
        namespace primitives
        {
            class VertexAttribute
            {
            public:
                VertexAttribute(enumerators::AttributeType attributeType, enumerators::DataType dataType, int noOfComponents, int noOfBytesPerComponent, bool isNormalised);

                enumerators::AttributeType GetAttributeType() const;
                enumerators::DataType GetDataType() const;
                bool GetIsNormalised() const;
                int GetNoOfBytes() const;
                int GetNoOfComponents() const;

            private:
                enumerators::AttributeType _attributeType;
                enumerators::DataType _dataType;
                int _noOfComponents{ 0 };
                int _noOfBytes{ 0 };
                bool _isNormalised{ 0 };
            };
        }
    }
}