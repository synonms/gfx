#pragma once

#include <glproxy\glproxy-exports.h>

#include <glproxy\enumerators\data-type.h>

namespace synonms
{
    namespace gfx
    {
        namespace proxies
        {
            namespace opengl
            {
                class VertexAttributeArray
                {
                public:
                    GLPROXY_API static void Configure(unsigned int index, int noOfComponentsPerAttribute, enumerators::DataType dataType, int noOfBytesPerVertex, bool isNormalised, unsigned int offset, bool throwOnError = false);
                    GLPROXY_API static void Enable(unsigned int index, bool throwOnError = false);
                };
            }
        }
    }
}
