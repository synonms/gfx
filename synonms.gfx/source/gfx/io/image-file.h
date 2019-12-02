#pragma once

#include <string>

namespace synonms
{
    namespace gfx
    {
        namespace io
        {
            class ImageFile
            {
            public:
                ImageFile();
                ImageFile(ImageFile&& other) noexcept;
                ImageFile& operator=(ImageFile&& other) noexcept;
                ~ImageFile();

                ImageFile(const ImageFile& other) = delete;
                ImageFile& operator=(const ImageFile& other) = delete;

                unsigned char* data{ nullptr };
                int width{ 0 };
                int height{ 0 };
                int bitsPerPixel{ 0 };
                std::string error{ "" };
            };
        }
    }
}
