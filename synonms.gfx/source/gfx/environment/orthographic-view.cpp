#include "orthographic-view.h"

using namespace synonms::gfx::environment;
using namespace synonms::gfx::transforms;

OrthographicView::OrthographicView(float left, float right, float bottom, float top, float nearClipPlane, float farClipPlane)
{
    _projectionMatrix = Matrix4x4::CreateOrthographic(left, right, bottom, top, nearClipPlane, farClipPlane);
}

const Matrix4x4& OrthographicView::GetProjectionMatrix() const
{
    return _projectionMatrix;
}

void OrthographicView::Resize(float left, float right, float bottom, float top, float nearClipPlane, float farClipPlane)
{
    _projectionMatrix = Matrix4x4::CreateOrthographic(left, right, bottom, top, nearClipPlane, farClipPlane);
}
