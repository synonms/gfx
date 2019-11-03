#pragma once

#include <memory>

#include <gfx\mathematics\linear\matrix4x4.h>

namespace synonms
{
    namespace gfx
    {
        namespace environment
        {
            class PerspectiveView
            {
            public:
                PerspectiveView(float horizontalFieldOfView, float aspectRatio, float nearClipPlane, float farClipPlane);

                const mathematics::linear::Matrix4x4<float>& GetProjectionMatrix() const;
                void Resize(float horizontalFieldOfView, float aspectRatio, float nearClipPlane, float farClipPlane);

            private:
                mathematics::linear::Matrix4x4<float> _projectionMatrix;
            };
        }
    }
}
