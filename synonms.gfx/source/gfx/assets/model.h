#pragma once

#include <gfx\primitives\mesh-instance.h>

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
                ~Model();

                const std::vector<std::unique_ptr<primitives::MeshInstance>>& GetMeshInstances() const;

            private:
                class Implementation;
                std::unique_ptr<Implementation> _implementation;
            };
        }
    }
}