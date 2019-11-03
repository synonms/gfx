#pragma once

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
                    static void Bind(unsigned int id, bool throwOnError = false);
                    static void Draw(enumerators::DrawMode drawMode, int noOfIndices, enumerators::DataType dataType, bool throwOnError = false);
                    static unsigned int Generate(bool throwOnError = false);
                    static void SendData(const void* data, size_t noOfBytes, enumerators::DataUsage dataUsage, bool throwOnError = false);
                };
            }
        }
    }
}
