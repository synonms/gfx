#pragma once

#include <gfx\primitives\mesh.h>
#include <opengl\texture.h>

#include <memory>
#include <vector>

namespace synonms
{
    namespace gfx
    {
        namespace assets
        {
            class Model
            {
            public:
                Model(const std::string& filePath);

            private:
                class Implementation;
                std::unique_ptr<Implementation> _implementation;
            };
        }
    }
}