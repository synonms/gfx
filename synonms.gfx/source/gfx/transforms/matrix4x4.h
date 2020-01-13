#pragma once

#include <gfx\mathematics\maths-helper.h>
#include <gfx\geometry\bounds3.h>
#include <gfx\geometry\normal3.h>
#include <gfx\geometry\point3.h>
#include <gfx\geometry\ray.h>
#include <gfx\geometry\vector3.h>
#include <gfx\geometry\vector4.h>
#include <gfx\transforms\matrix3x3.h>

namespace synonms
{
    namespace gfx
    {
        namespace transforms
        {
            class Matrix4x4
            {
            public:
                Matrix4x4(
                    float xAxisX = 1.0f, float xAxisY = 0.0f, float xAxisZ = 0.0f, float xAxisW = 0.0f,
                    float yAxisX = 0.0f, float yAxisY = 1.0f, float yAxisZ = 0.0f, float yAxisW = 0.0f,
                    float zAxisX = 0.0f, float zAxisY = 0.0f, float zAxisZ = 1.0f, float zAxisW = 0.0f,
                    float originX = 0.0f, float originY = 0.0f, float originZ = 0.0f, float originW = 1.0f)
                    : xAxis({ xAxisX, xAxisY, xAxisZ, xAxisW })
                    , yAxis({ yAxisX, yAxisY, yAxisZ, yAxisW })
                    , zAxis({ zAxisX, zAxisY, zAxisZ, zAxisW })
                    , origin({ originX, originY, originZ, originW })
                {
                }

                Matrix4x4(const geometry::Vector4<float>& xAxis, const geometry::Vector4<float>& yAxis, const geometry::Vector4<float>& zAxis, const geometry::Vector4<float>& origin)
                    : xAxis(xAxis)
                    , yAxis(yAxis)
                    , zAxis(zAxis)
                    , origin(origin)
                {
                }

                ///  X axis Y axis Z axis origin
                /// [scaleX 0      0      translationX]
                /// [0      scaleY 0      translationY]
                /// [0      0      scaleZ translationZ]
                /// [0      0      0      1           ]
                geometry::Vector4<float> xAxis;
                geometry::Vector4<float> yAxis;
                geometry::Vector4<float> zAxis;
                geometry::Vector4<float> origin;

            public:
                /// Determinant is the factor by which the area/volume represented by the basis vectors is increased/decreased by the transform
                /// e.g. with the matrix
                /// [ 2 0 ]
                /// [ 0 2 ]
                /// the area increases from 1x1 to 2x2 so the Determinant is 4
                /// Negative Determinant means that the plane is flipped (orientation of space is inverted) for 2D
                /// For 3D it means that the coordinate system has flipped from right handed to left handed
                float Determinant() const
                {
                    // plus a times the determinant of the matrix that is not in a's row or column,
                    auto determinantA = Matrix3x3(
                        yAxis.y,  yAxis.z,  yAxis.w, 
                        zAxis.y,  zAxis.z,  zAxis.w, 
                        origin.y, origin.z, origin.w)
                        .Determinant();
                    // minus b times the determinant of the matrix that is not in b's row or column,
                    auto determinantB = Matrix3x3(
                        xAxis.y,  xAxis.z,  xAxis.w, 
                        zAxis.y,  zAxis.z,  zAxis.w, 
                        origin.y, origin.z, origin.w)
                        .Determinant();
                    // plus c times the determinant of the matrix that is not in c's row or column,
                    auto determinantC = Matrix3x3(
                        xAxis.y,  xAxis.z,  xAxis.w, 
                        yAxis.y,  yAxis.z,  yAxis.w, 
                        origin.y, origin.z, origin.w)
                        .Determinant();
                    // minus d times the determinant of the matrix that is not in d's row or column,
                    auto determinantD = Matrix3x3(
                        xAxis.y, xAxis.z, xAxis.w, 
                        yAxis.y, yAxis.z, yAxis.w, 
                        zAxis.y, zAxis.z, zAxis.w)
                        .Determinant();

                    return (xAxis.x * determinantA) - (yAxis.x * determinantB) + (zAxis.x * determinantC) - (origin.x * determinantD);
                }

                const float* Data() const
                {
                    return &xAxis.x;
                }

                void GetEulerAngles(float& pitchDegrees, float& yawDegrees, float& rollDegrees) const
                {
                    pitchDegrees = mathematics::MathsHelper::ArcSine(-zAxis.y);

                    if (mathematics::MathsHelper::Cosine(pitchDegrees) == 0.0f) {
                        // Gimbal lock
                        yawDegrees = mathematics::MathsHelper::ArcTangent(-xAxis.z, xAxis.x);
                        rollDegrees = 0.0f;
                    }
                    else {
                        yawDegrees = mathematics::MathsHelper::ArcTangent(yAxis.x, yAxis.z);
                        rollDegrees = mathematics::MathsHelper::ArcTangent(xAxis.y, yAxis.y);
                    }

                    pitchDegrees = mathematics::MathsHelper::RadiansToDegrees(pitchDegrees);
                    yawDegrees = mathematics::MathsHelper::RadiansToDegrees(yawDegrees);
                    rollDegrees = mathematics::MathsHelper::RadiansToDegrees(rollDegrees);
                }

                geometry::Vector4<float> GetXRow() const
                {
                    return { xAxis.x, yAxis.x, zAxis.x, origin.x };
                }

                geometry::Vector4<float> GetYRow() const
                {
                    return { xAxis.y, yAxis.y, zAxis.y, origin.y };
                }

                geometry::Vector4<float> GetZRow() const
                {
                    return { xAxis.z, yAxis.z, zAxis.z, origin.z };
                }

                geometry::Vector4<float> GetWRow() const
                {
                    return { xAxis.w, yAxis.w, zAxis.w, origin.w };
                }

                /// Reset to Identity
                void Reset()
                {
                    xAxis.x = 1.0f; yAxis.x = 0.0f; zAxis.x = 0.0f; origin.x = 0.0f;
                    xAxis.y = 0.0f; yAxis.y = 1.0f; zAxis.y = 0.0f; origin.y = 0.0f;
                    xAxis.z = 0.0f; yAxis.z = 0.0f; zAxis.z = 1.0f; origin.z = 0.0f;
                    xAxis.w = 0.0f; yAxis.w = 0.0f; zAxis.w = 0.0f; origin.w = 1.0f;
                }

                void RotateAboutX(float angleInRadians)
                {
                    auto rotationMatrix = CreateFromRotationAboutX(angleInRadians);
                    *this = *this * rotationMatrix;
                }

                void RotateAboutY(float angleInRadians)
                {
                    auto rotationMatrix = CreateFromRotationAboutY(angleInRadians);
                    *this = *this * rotationMatrix;
                }

                void RotateAboutZ(float angleInRadians)
                {
                    auto rotationMatrix = CreateFromRotationAboutZ(angleInRadians);
                    *this = *this * rotationMatrix;
                }

                void RotateAboutAxis(float angleInRadians, const geometry::Vector3<float>& axis)
                {
                    auto rotationMatrix = CreateFromRotationAboutAxis(angleInRadians, axis);
                    *this = *this * rotationMatrix;
                }

                void RotateWithPitchYawRoll(float pitchInRadians, float yawInRadians, float rollInRadians)
                {
                    auto rotationMatrix = CreateFromRotationPitchYawRoll(pitchInRadians, yawInRadians, rollInRadians);
                    *this = *this * rotationMatrix;
                }

                void Scale(float xFactor, float yFactor, float zFactor)
                {
                    auto scaleMatrix = CreateFromScale({xFactor, yFactor, zFactor});
                    *this = *this * scaleMatrix;
                }

                geometry::Bounds3<float> Transform(const geometry::Bounds3<float>& bounds) const {
                    geometry::Bounds3<float> ret(Transform(geometry::Point3<float>(bounds.minimum.x, bounds.minimum.y, bounds.minimum.z)));
                    ret = geometry::Bounds3<float>::CreateUnion(ret, Transform(geometry::Point3<float>(bounds.maximum.x, bounds.minimum.y, bounds.minimum.z)));
                    ret = geometry::Bounds3<float>::CreateUnion(ret, Transform(geometry::Point3<float>(bounds.minimum.x, bounds.maximum.y, bounds.minimum.z)));
                    ret = geometry::Bounds3<float>::CreateUnion(ret, Transform(geometry::Point3<float>(bounds.minimum.x, bounds.minimum.y, bounds.maximum.z)));
                    ret = geometry::Bounds3<float>::CreateUnion(ret, Transform(geometry::Point3<float>(bounds.minimum.x, bounds.maximum.y, bounds.maximum.z)));
                    ret = geometry::Bounds3<float>::CreateUnion(ret, Transform(geometry::Point3<float>(bounds.maximum.x, bounds.maximum.y, bounds.minimum.z)));
                    ret = geometry::Bounds3<float>::CreateUnion(ret, Transform(geometry::Point3<float>(bounds.maximum.x, bounds.minimum.y, bounds.maximum.z)));
                    ret = geometry::Bounds3<float>::CreateUnion(ret, Transform(geometry::Point3<float>(bounds.maximum.x, bounds.maximum.y, bounds.maximum.z)));

                    return ret;
                }

                geometry::Normal3<float> Transform(const geometry::Normal3<float>& input) const
                {
                    auto inverse = Matrix4x4::CreateInverseOf(*this);

                    auto outputX = (inverse.xAxis.x * input.x) + (inverse.xAxis.y * input.y) + (inverse.xAxis.z * input.z);
                    auto outputY = (inverse.yAxis.x * input.x) + (inverse.yAxis.y * input.y) + (inverse.yAxis.z * input.z);
                    auto outputZ = (inverse.zAxis.x * input.x) + (inverse.zAxis.y * input.y) + (inverse.zAxis.z * input.z);

                    return { outputX, outputY, outputZ };
                }

                geometry::Point3<float> Transform(const geometry::Point3<float>& input) const
                {
                    float w = 1.0f;

                    auto outputX = (xAxis.x * input.x) + (yAxis.x * input.y) + (zAxis.x * input.z) + (origin.x * w);
                    auto outputY = (xAxis.y * input.x) + (yAxis.y * input.y) + (zAxis.y * input.z) + (origin.y * w);
                    auto outputZ = (xAxis.z * input.x) + (yAxis.z * input.y) + (zAxis.z * input.z) + (origin.z * w);
                    auto outputW = (xAxis.w * input.x) + (yAxis.w * input.y) + (zAxis.w * input.z) + (origin.w * w);

                    return geometry::Point3<float>(outputX, outputY, outputZ) / (outputW == 0.0f ? 1.0f : outputW);
                }

                inline geometry::Ray Transform(const geometry::Ray& input) const {
                    auto roundOffErrors = geometry::Vector3<float>();  // TODO - Should be generated by origin transform
                    auto origin = Transform(input.origin);
                    auto direction = Transform(input.direction);

                    // Offset ray origin to edge of error bounds and compute tMax
                    float lengthSquared = direction.Length() * direction.Length();
                    float tMax = input.maxExtent;

                    // TODO - Adjust origin to account for round off errors
//                        if (lengthSquared > 0) {
//                            auto dt = Vector3<float>::Abs(direction).Dot(roundOffErrors) / lengthSquared;
//                            origin += direction * dt;
//                            tMax -= dt;
//                        }

                    return geometry::Ray(origin, direction, tMax, input.time, input.medium);
                }

                geometry::Vector3<float> Transform(const geometry::Vector3<float>& input) const
                {
                    float w = 0.0f;

                    auto outputX = (xAxis.x * input.x) + (yAxis.x * input.y) + (zAxis.x * input.z) + (origin.x * w);
                    auto outputY = (xAxis.y * input.x) + (yAxis.y * input.y) + (zAxis.y * input.z) + (origin.y * w);
                    auto outputZ = (xAxis.z * input.x) + (yAxis.z * input.y) + (zAxis.z * input.z) + (origin.z * w);

                    return { outputX, outputY, outputZ };
                }

                void Translate(geometry::Vector3<float> delta)
                {
                    Translate(delta.x, delta.y, delta.z);
                }

                void Translate(float x, float y, float z)
                {
                    origin.x += x;
                    origin.y += y;
                    origin.z += z;
                }

            public:
                static Matrix3x3 Create3x3From(const Matrix4x4& matrix)
                {
                    return { 
                        matrix.xAxis.x, matrix.xAxis.y, matrix.xAxis.z,
                        matrix.yAxis.x, matrix.yAxis.y, matrix.yAxis.z,
                        matrix.zAxis.x, matrix.zAxis.y, matrix.zAxis.z
                    };
                }

                static Matrix4x4 CreateFromRotationAboutX(float angleInRadians)
                {
                    float cos_theta = mathematics::MathsHelper::Cosine(angleInRadians);
                    float sin_theta = mathematics::MathsHelper::Sine(angleInRadians);

                    return {
                        1.0f, 0.0f,      0.0f,       0.0f,
                        0.0f, cos_theta, -sin_theta, 0.0f,
                        0.0f, sin_theta, cos_theta,  0.0f,
                        0.0f, 0.0f,      0.0f,       1.0f
                    };
                }

                static Matrix4x4 CreateFromRotationAboutY(float angleInRadians)
                {
                    float cos_theta = mathematics::MathsHelper::Cosine(angleInRadians);
                    float sin_theta = mathematics::MathsHelper::Sine(angleInRadians);

                    return {
                        cos_theta,  0.0f, sin_theta, 0.0f,
                        0.0f,       1.0f, 0.0f,      0.0f,
                        -sin_theta, 0.0f, cos_theta, 0.0f,
                        0.0f,       0.0f, 0.0f,      1.0f
                    };
                }

                static Matrix4x4 CreateFromRotationAboutZ(float angleInRadians)
                {
                    float cos_theta = mathematics::MathsHelper::Cosine(angleInRadians);
                    float sin_theta = mathematics::MathsHelper::Sine(angleInRadians);

                    return {
                        cos_theta, -sin_theta, 0.0f, 0.0f,
                        sin_theta, cos_theta,  0.0f, 0.0f,
                        0.0f,      0.0f,       1.0f, 0.0f,
                        0.0f,      0.0f,       0.0f, 1.0f
                    };
                }

                static Matrix4x4 CreateFromRotationAboutAxis(float angleInRadians, const geometry::Vector3<float>& axis)
                {
                    float cos_theta = mathematics::MathsHelper::Cosine(angleInRadians);
                    float sin_theta = mathematics::MathsHelper::Sine(angleInRadians);
                    float one_minus_cos_theta = 1.0f - cos_theta;

                    Matrix4x4 result;
                    result.xAxis.x = axis.x * axis.x * one_minus_cos_theta + cos_theta;
                    result.yAxis.x = axis.x * axis.y * one_minus_cos_theta - axis.z * sin_theta;
                    result.zAxis.x = axis.x * axis.z * one_minus_cos_theta + axis.y * sin_theta;
                    result.xAxis.y = axis.x * axis.y * one_minus_cos_theta + axis.z * sin_theta;
                    result.yAxis.y = axis.y * axis.y * one_minus_cos_theta + cos_theta;
                    result.zAxis.y = axis.y * axis.z * one_minus_cos_theta - axis.x * sin_theta;
                    result.xAxis.z = axis.x * axis.z * one_minus_cos_theta - axis.y * sin_theta;
                    result.yAxis.z = axis.y * axis.z * one_minus_cos_theta + axis.x * sin_theta;
                    result.zAxis.z = axis.z * axis.z * one_minus_cos_theta + cos_theta;

                    return result;
                }

                static Matrix4x4 CreateFromRotationAxes(const geometry::Vector3<float>& xAxis, const geometry::Vector3<float>& yAxis, const geometry::Vector3<float>& zAxis)
                {
                    Matrix4x4 result;
                    result.xAxis.x = xAxis.x;	result.yAxis.x = yAxis.x;	result.zAxis.x = zAxis.x;	result.origin.x = 0.0f;
                    result.xAxis.y = xAxis.y;	result.yAxis.y = yAxis.y;	result.zAxis.y = zAxis.y;	result.origin.y = 0.0f;
                    result.xAxis.z = xAxis.z;	result.yAxis.z = yAxis.z;	result.zAxis.z = zAxis.z;	result.origin.z = 0.0f;
                    result.xAxis.w = 0.0f;      result.yAxis.w = 0.0f;      result.zAxis.w = 0.0f;      result.origin.w = 1.0f;

                    return result;
                }

                static Matrix4x4 CreateFromRotationPitchYawRoll(float pitchRadians, float yawRadians, float rollRadians)
                {
                    // Roll then Pitch then Yaw
                    auto cos_pitch = mathematics::MathsHelper::Cosine(pitchRadians);
                    auto sin_pitch = mathematics::MathsHelper::Sine(pitchRadians);
                    auto cos_yaw = mathematics::MathsHelper::Cosine(yawRadians);
                    auto sin_yaw = mathematics::MathsHelper::Sine(yawRadians);
                    auto cos_roll = mathematics::MathsHelper::Cosine(rollRadians);
                    auto sin_roll = mathematics::MathsHelper::Sine(rollRadians);

                    Matrix4x4 result;
                    result.xAxis.x = (cos_yaw * cos_roll) + (sin_yaw * sin_pitch * sin_roll);
                    result.yAxis.x = -(cos_yaw * sin_roll) + (sin_yaw * sin_pitch * cos_roll);
                    result.zAxis.x = sin_yaw * cos_pitch;
                    result.xAxis.y = sin_roll * cos_pitch;
                    result.yAxis.y = cos_roll * cos_pitch;
                    result.zAxis.y = -sin_pitch;
                    result.xAxis.z = -(sin_yaw * cos_roll) + (cos_yaw * sin_pitch * sin_roll);
                    result.yAxis.z = (sin_roll * sin_yaw) + (cos_yaw * sin_pitch * cos_roll);
                    result.zAxis.z = cos_yaw * cos_pitch;

                    return result;
                }

                static Matrix4x4 CreateFromScale(const geometry::Vector3<float>& scale)
                {
                    Matrix4x4 result;
                    result.xAxis.x = scale.x;
                    result.yAxis.y = scale.y;
                    result.zAxis.z = scale.z;

                    return result;
                }

                static Matrix4x4 CreateFromTranslation(float x, float y, float z)
                {
                    Matrix4x4 result;
                    result.origin.x = x;
                    result.origin.y = y;
                    result.origin.z = z;
 
                    return result;
                }

                static Matrix4x4 CreateFromTranslation(const geometry::Vector3<float>& translation)
                {
                    return CreateFromTranslation(translation.x, translation.y, translation.z);
                }

                static Matrix3x3 CreateNormalFrom(const Matrix4x4& matrix)
                {
                    return Matrix3x3::CreateTransposeOf(Matrix3x3::CreateInverseOf(Create3x3From(matrix)));
                }

                static Matrix4x4 CreateViewFrom(const geometry::Point3<float>& position, const geometry::Vector3<float>& rotationDegrees, bool isRotationOnly)
                {
                    Matrix4x4 translation;

                    if (!isRotationOnly) {
                        // Move camera to origin
                        translation = Matrix4x4::CreateFromTranslation(-position.x, -position.y, -position.z);
                    }

                    auto rotationMatrix = Matrix4x4::CreateFromRotationPitchYawRoll(
                        mathematics::MathsHelper::DegreesToRadians(rotationDegrees.pitch),
                        mathematics::MathsHelper::DegreesToRadians(rotationDegrees.yaw),
                        mathematics::MathsHelper::DegreesToRadians(rotationDegrees.roll));

                    auto inverseRotation = Matrix4x4::CreateInverseOf(rotationMatrix);

                    return inverseRotation * translation;
                }

                static Matrix4x4 CreateViewFrom(const geometry::Point3<float>& eyePosition, const geometry::Point3<float>& targetPosition, const geometry::Vector3<float>& worldUpDirection = { 0.0f, 1.0f, 0.0f })
                {
                    // Forward actually points away from the target
                    auto forward = targetPosition.VectorTo(eyePosition);
                    forward.Normalise();

                    auto right = worldUpDirection.Cross(forward);
                    right.Normalise();

                    auto up = forward.Cross(right);
                    up.Normalise();

                    auto originToEye = geometry::Point3<float>().VectorTo(eyePosition);

                    // Transformations are transposed
                    return {
                        right.x,                  up.x,                 forward.x,                0.0f,
                        right.y,                  up.y,                 forward.y,                0.0f, 
                        right.z,                  up.z,                 forward.z,                0.0f,
                        -right.Dot(originToEye), -up.Dot(originToEye), -forward.Dot(originToEye), 1.0f
                    };
                }

                static Matrix4x4 CreateOrthographic(float left, float right, float bottom, float top, float near, float far)
                {
                    auto horizontal_zoom = 2.0f / (right - left);
                    auto vertical_zoom = 2.0f / (top - bottom);

                    auto i = geometry::Vector4<float>(horizontal_zoom, 0.0f, 0.0f, 0.0f);
                    auto j = geometry::Vector4<float>(0.0f, vertical_zoom, 0.0f, 0.0f);
                    auto k = geometry::Vector4<float>(0.0f, 0.0f, -2.0f / (far - near), 0.0f);
                    auto l = geometry::Vector4<float>(0.0f, 0.0f, -((near + far) / (far - near)), 1.0f);

                    return { i, j, k, l };
                }

                static Matrix4x4 CreateInverseOf(const Matrix4x4& matrix)
                {
                    Matrix4x4 result;

                    // Check it's not a singular matrix which has no inverse
                    if (matrix.Determinant() != 0.0f) 
                    {
                        auto cofactorMatrix = Create3x3From(matrix).Cofactor();
                        // Get the cofactor for each element in the 3x3 matrix and transpose
                        // Invert the translation elements
                        result.xAxis.x = cofactorMatrix.xAxis.x; result.yAxis.x = cofactorMatrix.xAxis.y; result.zAxis.x = cofactorMatrix.xAxis.z; result.origin.x = -matrix.origin.x;
                        result.xAxis.y = cofactorMatrix.yAxis.x; result.yAxis.y = cofactorMatrix.yAxis.y; result.zAxis.y = cofactorMatrix.yAxis.z; result.origin.y = -matrix.origin.y;
                        result.xAxis.z = cofactorMatrix.zAxis.x; result.yAxis.z = cofactorMatrix.zAxis.y; result.zAxis.z = cofactorMatrix.zAxis.z; result.origin.z = -matrix.origin.z;
                    }

                    return result;
                }

                static Matrix4x4 CreatePerspective(float horizontalFieldOfViewRadians, float aspectRatio, float near, float far)
                {
                    auto scaleY = 1.0f / mathematics::MathsHelper::Tangent(horizontalFieldOfViewRadians / 2.0f);
                    auto scaleX = scaleY / aspectRatio;

                    auto i = geometry::Vector4<float>(scaleX, 0.0f, 0.0f, 0.0f);
                    auto j = geometry::Vector4<float>(0.0f, scaleY, 0.0f, 0.0f);
                    auto k = geometry::Vector4<float>(0.0f, 0.0f, ((far + near) / (near - far)), -1.0f);
                    auto l = geometry::Vector4<float>(0.0f, 0.0f, (2.0f * near * far) / (near - far), 0.0f);

                    return { i, j, k, l };
                }

            public:
                friend Matrix4x4 operator*(const Matrix4x4& left, const Matrix4x4& right) {
                    return {
                        left.GetXRow().Dot(right.xAxis),
                        left.GetYRow().Dot(right.xAxis),
                        left.GetZRow().Dot(right.xAxis),
                        left.GetWRow().Dot(right.xAxis),

                        left.GetXRow().Dot(right.yAxis),
                        left.GetYRow().Dot(right.yAxis),
                        left.GetZRow().Dot(right.yAxis),
                        left.GetWRow().Dot(right.yAxis),

                        left.GetXRow().Dot(right.zAxis),
                        left.GetYRow().Dot(right.zAxis),
                        left.GetZRow().Dot(right.zAxis),
                        left.GetWRow().Dot(right.zAxis),

                        left.GetXRow().Dot(right.origin),
                        left.GetYRow().Dot(right.origin),
                        left.GetZRow().Dot(right.origin),
                        left.GetWRow().Dot(right.origin),
                    };
                }

                friend Matrix4x4 operator*(const Matrix4x4& matrix, float factor) {
                    return {
                        matrix.xAxis.x  * factor, matrix.xAxis.y  * factor, matrix.xAxis.z  * factor,
                        matrix.yAxis.x  * factor, matrix.yAxis.y  * factor, matrix.yAxis.z  * factor,
                        matrix.zAxis.x  * factor, matrix.zAxis.y  * factor, matrix.zAxis.z  * factor,
                        matrix.origin.x * factor, matrix.origin.y * factor, matrix.origin.z * factor
                    };
                }
            };
        }
    }
}