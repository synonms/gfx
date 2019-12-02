#include "image-file.h"

#include <vendor\stb_image\stb-image.h>

using namespace synonms::gfx::io;

ImageFile::ImageFile()
    : data(nullptr)
    , width(0)
    , height(0)
    , bitsPerPixel(0)
    , error("")
{
}

ImageFile::ImageFile(ImageFile&& other) noexcept
    : data(std::exchange(other.data, nullptr))
    , width(std::exchange(other.width, 0))
    , height(std::exchange(other.height, 0))
    , bitsPerPixel(std::exchange(other.bitsPerPixel, 0))
    , error(std::exchange(other.error, ""))
{
}

ImageFile& ImageFile::operator=(ImageFile&& other) noexcept
{
    data = std::exchange(other.data, nullptr);
    width = std::exchange(other.width, 0);
    height = std::exchange(other.height, 0);
    bitsPerPixel = std::exchange(other.bitsPerPixel, 0);
    error = std::exchange(other.error, "");

    return *this;
}

ImageFile::~ImageFile()
{
    if (data) {
        stbi_image_free(data);
    }
}
