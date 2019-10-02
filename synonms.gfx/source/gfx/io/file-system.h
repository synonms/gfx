#pragma once

#include <gfx\exports.h>

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
                SYNONMS_GFX_API std::string ReadFile(const std::string& filePath);
            };
        }
    }
}
