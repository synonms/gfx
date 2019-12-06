#pragma once

#include <opengl\texture.h>

#include <memory>

namespace synonms
{
    namespace gfx
    {
        namespace api
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
