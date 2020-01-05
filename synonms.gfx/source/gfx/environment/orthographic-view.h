#pragma once

#include <memory>

#include <gfx\environment\i-view.h>
#include <gfx\transforms\matrix4x4.h>

namespace synonms
{
    namespace gfx
    {
        namespace environment
        {
            class OrthographicView : public IView
            {
            public:
                OrthographicView(float left, float right, float bottom, float top, float nearClipPlane, float farClipPlane);

                virtual const transforms::Matrix4x4& GetProjectionMatrix() const override;
                void Resize(float left, float right, float bottom, float top, float nearClipPlane, float farClipPlane);

            private:
                transforms::Matrix4x4 _projectionMatrix;
            };
        }
    }
}
