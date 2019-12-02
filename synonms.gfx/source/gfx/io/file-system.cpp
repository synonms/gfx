#include "file-system.h"

#include <vendor\stb_image\stb-image.h>

#include <fstream>

using namespace synonms::gfx::io;

std::string FileSystem::ReadFile(const std::string& filePath)
{
    std::ifstream stream(filePath);

    if (stream.is_open())
    {
        return { std::istreambuf_iterator<char>(stream), std::istreambuf_iterator<char>() };
    }

    return "";
}

ImageFile FileSystem::ReadImage(const std::string& filePath)
{
    ImageFile result;

    // OpenGL expects images with 0,0 at bottom left which isn't how PNG stores the data, so we need to flip it
    stbi_set_flip_vertically_on_load(1);
    result.data = stbi_load(filePath.c_str(), &result.width, &result.height, &result.bitsPerPixel, 4); // 4 = RGBA

    if (!result.data)
    {
        auto message = stbi_failure_reason();
        result.error = std::string(message);
    }

    return std::move(result);
}
