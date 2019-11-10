#include "perspective-view.h"

#include <gfx\mathematics\maths-helper.h>

using namespace synonms::gfx::environment;
using namespace synonms::gfx::mathematics;
using namespace synonms::gfx::mathematics::linear;

PerspectiveView::PerspectiveView(float horizontalFieldOfViewDegrees, float aspectRatio, float nearClipPlane, float farClipPlane)
{
    _projectionMatrix = Matrix4x4<float>::CreatePerspective(MathsHelper::DegreesToRadians(horizontalFieldOfViewDegrees), aspectRatio, nearClipPlane, farClipPlane);
}

const Matrix4x4<float>& PerspectiveView::GetProjectionMatrix() const
{
    return _projectionMatrix;
}

void PerspectiveView::Resize(float horizontalFieldOfViewDegrees, float aspectRatio, float nearClipPlane, float farClipPlane)
{
    _projectionMatrix = Matrix4x4<float>::CreatePerspective(MathsHelper::DegreesToRadians(horizontalFieldOfViewDegrees), aspectRatio, nearClipPlane, farClipPlane);
}
