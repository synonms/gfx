#pragma once

#include <glproxy\enumerators\attribute-bit.h>

namespace synonms
{
    namespace gfx
    {
        namespace proxies
        {
            namespace opengl
            {
                class Renderer
                {
                public:
                    static void Clear(enumerators::AttributeBit attributeBit = enumerators::AttributeBit::ColourBuffer);
                    static void ClearColour(float red, float green, float blue, float alpha);
                    static void ClearDepth(double value);
                    static void ClearStencil(int value);
                };
            }
        }
    }
}
