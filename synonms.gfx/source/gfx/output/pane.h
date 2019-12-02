#pragma once

#include <gfx\primitives\mesh.h>

#include <memory>

namespace synonms
{
    namespace gfx
    {
        namespace output
        {
            class Pane
            {
            public:
                Pane(float left, float bottom, float width, float height);

                inline primitives::Mesh& GetMesh() { return *_mesh.get(); }

            private:
                float _left;
                float _bottom;
                float _width;
                float _height;
                std::unique_ptr<primitives::Mesh> _mesh;
            };
        }
    }
}