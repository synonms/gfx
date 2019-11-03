#include "perspective-view.h"

using namespace synonms::gfx::environment;
using namespace synonms::gfx::mathematics::linear;

PerspectiveView::PerspectiveView(float horizontalFieldOfView, float aspectRatio, float nearClipPlane, float farClipPlane)
{
    _projectionMatrix = Matrix4x4<float>::CreatePerspective(horizontalFieldOfView, aspectRatio, nearClipPlane, farClipPlane);
}

const Matrix4x4<float>& PerspectiveView::GetProjectionMatrix() const
{
    return _projectionMatrix;
}

void PerspectiveView::Resize(float horizontalFieldOfView, float aspectRatio, float nearClipPlane, float farClipPlane)
{
    _projectionMatrix = Matrix4x4<float>::CreatePerspective(horizontalFieldOfView, aspectRatio, nearClipPlane, farClipPlane);
}
