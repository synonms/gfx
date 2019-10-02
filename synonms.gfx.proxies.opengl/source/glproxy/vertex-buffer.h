#pragma once

#include <glproxy\glproxy-exports.h>

#include <glproxy\enumerators\data-usage.h>

namespace synonms
{
    namespace gfx
    {
        namespace proxies
        {
            namespace opengl
            {
                class VertexBuffer
                {
                public:
                    GLPROXY_API static void Bind(unsigned int vertexBufferId, bool throwOnError = false);
                    GLPROXY_API static unsigned int Generate(bool throwOnError = false);
                    GLPROXY_API static void SendData(const void* data, size_t noOfBytes, enumerators::DataUsage dataUsage, bool throwOnError = false);
                };
            }
        }
    }
}
