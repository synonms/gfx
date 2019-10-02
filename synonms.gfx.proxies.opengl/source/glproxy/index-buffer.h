#pragma once

#include <glproxy\glproxy-exports.h>

#include <glproxy\enumerators\data-type.h>
#include <glproxy\enumerators\data-usage.h>
#include <glproxy\enumerators\draw-mode.h>

namespace synonms
{
    namespace gfx
    {
        namespace proxies
        {
            namespace opengl
            {
                class IndexBuffer
                {
                public:
                    GLPROXY_API static void Bind(unsigned int id, bool throwOnError = false);
                    GLPROXY_API static void Draw(enumerators::DrawMode drawMode, int noOfIndices, enumerators::DataType dataType, bool throwOnError = false);
                    GLPROXY_API static unsigned int Generate(bool throwOnError = false);
                    GLPROXY_API static void SendData(const void* data, size_t noOfBytes, enumerators::DataUsage dataUsage, bool throwOnError = false);
                };
            }
        }
    }
}
