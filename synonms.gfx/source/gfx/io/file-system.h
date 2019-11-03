#pragma once

#include <string>

namespace synonms
{
    namespace gfx
    {
        namespace io
        {
            class FileSystem
            {
            public:
                std::string ReadFile(const std::string& filePath);
            };
        }
    }
}
