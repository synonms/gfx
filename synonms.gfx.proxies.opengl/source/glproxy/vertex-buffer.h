#pragma once

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
                    static void Bind(unsigned int vertexBufferId, bool throwOnError = false);
                    static unsigned int Generate(bool throwOnError = false);
                    static void SendData(const void* data, size_t noOfBytes, enumerators::DataUsage dataUsage, bool throwOnError = false);
                };
            }
        }
    }
}
