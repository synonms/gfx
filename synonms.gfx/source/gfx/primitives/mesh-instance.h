#pragma once

#include <gfx\primitives\mesh.h>
#include <gfx\mathematics\linear\transform.h>

#include <string>

namespace synonms
{
    namespace gfx
    {
        namespace primitives
        {
            class MeshInstance
            {
            public:
                MeshInstance(const Mesh& mesh);

                mathematics::linear::Transform& GetTransform();

            private:
                const Mesh& _mesh;
                mathematics::linear::Transform _transform{};
            };
        }
    }
}