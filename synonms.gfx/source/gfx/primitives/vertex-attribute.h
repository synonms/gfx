#pragma once

#include <gfx\exports.h>
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
                SYNONMS_GFX_API VertexAttribute(enumerators::AttributeType attributeType, enumerators::DataType dataType, int noOfComponents, int noOfBytesPerComponent, bool isNormalised);

                SYNONMS_GFX_API enumerators::AttributeType GetAttributeType() const;
                SYNONMS_GFX_API enumerators::DataType GetDataType() const;
                SYNONMS_GFX_API bool GetIsNormalised() const;
                SYNONMS_GFX_API int GetNoOfBytes() const;
                SYNONMS_GFX_API int GetNoOfComponents() const;

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