#pragma once

#include <glproxy\glproxy-exports.h>

#include <glproxy\enumerators\data-type.h>
#include <glproxy\enumerators\data-usage.h>
#include <glproxy\enumerators\draw-mode.h>
#include <glproxy\enumerators\target-buffer.h>

namespace synonms
{
    namespace gfx
    {
        namespace proxies
        {
            namespace opengl
            {
                class Buffer
                {
                public:
                    GLPROXY_API static void Bind(enumerators::TargetBuffer targetBuffer, unsigned int id, bool throwOnError = false);
                    GLPROXY_API static unsigned int Generate(bool throwOnError = false);
                    GLPROXY_API static void SendData(enumerators::TargetBuffer targetBuffer, const void* data, size_t noOfBytes, enumerators::DataUsage dataUsage, bool throwOnError = false);
                };
            }
        }
    }
}
