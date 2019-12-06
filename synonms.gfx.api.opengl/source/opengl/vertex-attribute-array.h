#pragma once

#include <opengl\enumerators\data-type.h>

namespace synonms
{
    namespace gfx
    {
        namespace api
        {
            namespace opengl
            {
                class VertexAttributeArray
                {
                public:
                    static void Configure(unsigned int index, int noOfComponentsPerAttribute, enumerators::DataType dataType, int noOfBytesPerVertex, bool isNormalised, unsigned int offset);
                    static void Enable(unsigned int index);
                };
            }
        }
    }
}
