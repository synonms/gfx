#pragma once

#include <gfx\io\image-file.h>

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
                ImageFile ReadImage(const std::string& filePath);
            };
        }
    }
}
