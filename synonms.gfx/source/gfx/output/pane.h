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
                Pane(int leftPixels, int bottomPixels, int widthPixels, int heightPixels);

                void Resize(int leftPixels, int bottomPixels, int widthPixels, int heightPixels);
                void SetAsViewport() const;

            private:
                int _leftPixels;
                int _bottomPixels;
                int _widthPixels;
                int _heightPixels;
            };
        }
    }
}