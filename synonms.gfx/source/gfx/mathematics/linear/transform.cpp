#include "transform.h"

using namespace synonms::gfx::mathematics::linear;

const Vector3<float> Transform::WorldXAxis = Vector3<float>(1.0f, 0.0f, 0.0f);
const Vector3<float> Transform::WorldYAxis = Vector3<float>(0.0f, 1.0f, 0.0f);
const Vector3<float> Transform::WorldZAxis = Vector3<float>(0.0f, 0.0f, 1.0f);

Transform::Transform(TransformBehaviour behaviour)
    : behaviour(behaviour)
{
}

//void Transform::LookAt(const Vector3<float>& target)
//{
//    LookAt(_position, target, _yAxis);
//}

//void Transform::LookAt(const Vector3<float>& eye, const Vector3<float>& target, const Vector3<float>& up)
//{
//    _position = eye;
//    
//    SetZAxis(eye - target);
//    SetXAxis(up.Cross(_zAxis));
//    SetYAxis(_zAxis.Cross(_xAxis));
//
//    // Extract the angles
//    GetRotationMatrix().GetEulerAngles(_pitchInDegrees, _yawInDegrees, _rollInDegrees);
//}

//void Transform::Rotate(float pitchInDegrees, float yawInDegrees, float rollInDegrees)
//{
//    // Rotates the transform based on its current behavior.
//    // Note that not all behaviors support rolling.
//
//    switch (_behaviour)
//    {
//    case TransformBehaviour::FirstPerson:
//        RotateFirstPerson(pitchInDegrees, yawInDegrees);
//        break;
//
//    case TransformBehaviour::Flight:
//        RotateFlight(pitchInDegrees, yawInDegrees, rollInDegrees);
//        break;
//    }
//}
//
//void Transform::Scale(const Vector3<float>& scale)
//{
//
//}
//
//void Transform::Translate(float deltaX, float deltaY, float deltaZ)
//{
//    // Moves by dx world units to the left or right; dy world units upwards or downwards; and dz world units forwards or backwards.
//
//    auto forward = _zAxis;
//
//    if (_behaviour == TransformBehaviour::FirstPerson) {
//        // Calculate the forwards direction.
//        // Can't just use the camera's local z axis as doing so will cause the camera to move more slowly as the camera's view approaches 90 degrees straight up and down.
//        forward = WorldYAxis.Cross(_xAxis);
//        forward.Normalise();
//    }
//
//    auto translation = (_xAxis * deltaX) + (WorldYAxis * deltaY) + (forward * deltaZ);
//
//    _position += translation;
//}
//
//void Transform::TranslateAbsolute(const Vector3<float>& deltaTranslation)
//{
//    _position += deltaTranslation;
//}

Matrix3x3 Transform::GetNormalMatrix() const
{
    return Matrix4x4::CreateNormalFrom(GetModelMatrix());
}

Matrix4x4 Transform::GetTranslationMatrix() const
{
    return Matrix4x4::CreateFromTranslation(position);
}

Matrix4x4 Transform::GetRotationMatrix() const
{
    return Matrix4x4::CreateFromRotationPitchYawRoll(
        MathsHelper::DegreesToRadians(rotationDegrees.pitch), 
        MathsHelper::DegreesToRadians(rotationDegrees.yaw), 
        MathsHelper::DegreesToRadians(rotationDegrees.roll));
//    return Matrix4x4::CreateFromRotationAxes(_xAxis, _yAxis, _zAxis);
}

Matrix4x4 Transform::GetScaleMatrix() const
{
    return Matrix4x4::CreateFromScale(scale);
}

Matrix4x4 Transform::GetModelMatrix() const
{
//    return GetScaleMatrix() * GetRotationMatrix() * GetTranslationMatrix();
    return GetTranslationMatrix() * (GetRotationMatrix() * GetScaleMatrix());
}

Matrix4x4 Transform::GetViewMatrix(bool isRotationOnly) const
{
    Matrix4x4 translation;

    if (!isRotationOnly) {
        // Move camera to origin
        translation = Matrix4x4::CreateFromTranslation(-position.x, -position.y, -position.z);
    }

    auto rotation = Matrix4x4::CreateInverseOf(GetRotationMatrix());

    return rotation * translation;
}

void Transform::Reset()
{
    position.x = 0.0f; position.y = 0.0f; position.z = 0.0f;
    rotationDegrees.pitch = 0.0f; rotationDegrees.yaw = 0.0f; rotationDegrees.roll = 0.0f;
    scale.x = 1.0f; scale.y = 1.0f; scale.z = 1.0f;
    //    _xAxis.x = 1.0f; _xAxis.y = 0.0f; _xAxis.z = 0.0f;
//    _yAxis.x = 0.0f; _yAxis.y = 1.0f; _yAxis.z = 0.0f;
//    _zAxis.x = 0.0f; _zAxis.y = 0.0f; _zAxis.z = 1.0f;
//    _viewDirection.x = 0.0f; _viewDirection.y = 0.0f; _viewDirection.z = -1.0f;
}



//void Transform::RotateFlight(float pitchInDegrees, float yawInDegrees, float rollInDegrees)
//{
//    auto rotation = Matrix4x4::CreateFromRotationPitchYawRoll(MathsHelper::DegreesToRadians(pitchInDegrees), MathsHelper::DegreesToRadians(yawInDegrees), MathsHelper::DegreesToRadians(rollInDegrees));
//
//    auto transformedXAxis = rotation.Transform(_xAxis);
//    auto transformedYAxis = rotation.Transform(_yAxis);
//    auto transformedZAxis = rotation.Transform(_zAxis);
//
//    SetXAxis(transformedXAxis);
//    SetYAxis(transformedYAxis);
//    SetZAxis(transformedZAxis);
//}
//
//void Transform::RotateFirstPerson(float pitchInDegrees, float yawInDegrees)
//{
//    _rotationDegrees.pitch += MathsHelper::DegreesToRadians(pitchInDegrees);
//    _rotationDegrees.yaw += MathsHelper::DegreesToRadians(yawInDegrees);
//
//    // Hard limit pitch to -90...+90
//    if (_rotationDegrees.pitch > MathsHelper::DegreesToRadians(90.0f)) {
//        _rotationDegrees.pitch = MathsHelper::DegreesToRadians(90.0f);
//    }
//    else if (_rotationDegrees.pitch < -MathsHelper::DegreesToRadians(90.0f)) {
//        _rotationDegrees.pitch = -MathsHelper::DegreesToRadians(90.0f);
//    }
//
//    // Clock yaw to -180...+180
//    while (_rotationDegrees.yaw > MathsHelper::DegreesToRadians(180.0f)) {
//        _rotationDegrees.yaw -= MathsHelper::DegreesToRadians(360.0f);
//    }
//
//    while (_rotationDegrees.yaw < -MathsHelper::DegreesToRadians(180.0f)) {
//        _rotationDegrees.yaw += MathsHelper::DegreesToRadians(360.0f);
//    }
//
////    SetRotation(Matrix4x4::CreateFromRotationPitchYawRoll(MathsHelper::DegreesToRadians(_pitchInDegrees), MathsHelper::DegreesToRadians(_yawInDegrees), 0.0f));
//}

//void Transform::SetXAxis(const Vector3<float>& x)
//{
//    _xAxis = x;
//    _xAxis.Normalise();
//}
//
//void Transform::SetYAxis(const Vector3<float>& y)
//{
//    _yAxis = y;
//    _yAxis.Normalise();
//}
//
//void Transform::SetZAxis(const Vector3<float>& z)
//{
//    _zAxis = z;
//    _zAxis.Normalise();
//    SetViewDirection(Vector3<float>::CreateInverseOf(_zAxis));
//}