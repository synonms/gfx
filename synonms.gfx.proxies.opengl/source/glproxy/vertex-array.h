#pragma once

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
                    static void Bind(unsigned int vertexArrayId, bool throwOnError = false);
                    static unsigned int Generate(bool throwOnError = false);
                };
            }
        }
    }
}
