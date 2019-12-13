#pragma once

#include <opengl\texture.h>

#include <opengl\enumerators\data-type.h>
#include <opengl\enumerators\texture-format.h>
#include <opengl\enumerators\texture-internal-format.h>

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
                        static std::shared_ptr<Texture> CreateColour(int width, int height, 
                            unsigned char* data = nullptr, 
                            enumerators::TextureInternalFormat internalFormat = enumerators::TextureInternalFormat::RGB8, 
                            enumerators::TextureFormat format = enumerators::TextureFormat::RGBA, 
                            enumerators::DataType dataType = enumerators::DataType::UnsignedByte);
                        static std::shared_ptr<Texture> CreateDepth(int width, int height, unsigned char* data = nullptr);
                    };
                }
            }
        }
    }
}
