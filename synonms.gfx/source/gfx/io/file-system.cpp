#include "file-system.h"

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