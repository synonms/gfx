#pragma once

#include <glproxy\texture.h>

#include <memory>

namespace synonms
{
    namespace gfx
    {
        namespace proxies
        {
            namespace opengl
            {
                namespace factories
                {
                    class TextureFactory
                    {
                    public:
                        static std::shared_ptr<Texture> CreateColour(int width, int height, unsigned char* data = nullptr);
                        static std::shared_ptr<Texture> CreateDepth(int width, int height, unsigned char* data = nullptr);
                    };
                }
            }
        }
    }
}
