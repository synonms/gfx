#pragma once

#include <glproxy\glproxy-exports.h>

namespace synonms
{
    namespace gfx
    {
        namespace proxies
        {
            namespace opengl
            {
                class VertexArray
                {
                public:
                    GLPROXY_API static void Bind(unsigned int vertexArrayId, bool throwOnError = false);
                    GLPROXY_API static unsigned int Generate(bool throwOnError = false);
                };
            }
        }
    }
}
