#pragma once

#include <gfx\mathematics\maths-helper.h>
#include <gfx\mathematics\linear\matrix3x3.h>
#include <gfx\mathematics\linear\vector4.h>

namespace synonms
{
    namespace gfx
    {
        namespace mathematics
        {
            namespace linear
            {
                /// Given three basis vectors I (1.0, 0.0, 0.0), J (0.0, 1.0, 0.0) and K (0.0, 0.0, 1.0), 
                /// a 3x3 matrix represents a linear transformation by holding the resulting positions of I, J and K:
                ///   I J K
                /// [ x x x ]
                /// [ y y y ]
                /// [ z z z ]
                /// e.g. the matrix
                /// [ 2 0 0 ]
                /// [ 0 2 0 ]
                /// [ 0 0 2 ]
                /// represents scaling by factor 2, as I is transformed from (1, 0, 0) to (2, 0, 0), J from (0, 1, 0) to (0, 2, 0) and K from (0, 0, 1) to (0, 0, 2)
                /// An input vector of (3, 2, 1) would be transfornmed to (6, 4, 2) by this matrix
                template <typename T>
                class Matrix4x4
                {
                public:
                    Matrix4x4(
                        T vectorIx = static_cast<T>(1), T vectorIy = static_cast<T>(0), T vectorIz = static_cast<T>(0), T vectorIw = static_cast<T>(0),
                        T vectorJx = static_cast<T>(0), T vectorJy = static_cast<T>(1), T vectorJz = static_cast<T>(0), T vectorJw = static_cast<T>(0),
                        T vectorKx = static_cast<T>(0), T vectorKy = static_cast<T>(0), T vectorKz = static_cast<T>(1), T vectorKw = static_cast<T>(0),
                        T vectorLx = static_cast<T>(0), T vectorLy = static_cast<T>(0), T vectorLz = static_cast<T>(0), T vectorLw = static_cast<T>(1))
                        : iX(vectorIx), jX(vectorJx), kX(vectorKx), lX(vectorLx)
                        , iY(vectorIy), jY(vectorJy), kY(vectorKy), lY(vectorLy)
                        , iZ(vectorIz), jZ(vectorJz), kZ(vectorKz), lZ(vectorLz)
                        , iW(vectorIw), jW(vectorJw), kW(vectorKw), lW(vectorLw)
                    {
                    }

                    Matrix4x4(const Vector4<T>& vectorI, const Vector4<T>& vectorJ, const Vector4<T>& vectorK, const Vector4<T>& vectorL)
                        : iX(vectorI.x), jX(vectorJ.x), kX(vectorK.x), lX(vectorL.x)
                        , iY(vectorI.y), jY(vectorJ.y), kY(vectorK.y), lY(vectorL.y)
                        , iZ(vectorI.z), jZ(vectorJ.z), kZ(vectorK.z), lZ(vectorL.z)
                        , iW(vectorI.w), jW(vectorJ.w), kW(vectorK.w), lW(vectorL.w)
                    {
                    }

                    T iX, jX, kX, lX;
                    T iY, jY, kY, lY;
                    T iZ, jZ, kZ, lZ;
                    T iW, jW, kW, lW;

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
                        auto determinantA = Matrix3x3<T>(jY, jZ, jW, kY, kZ, kW, lY, lZ, lW).Determinant();
                        // minus b times the determinant of the matrix that is not in b's row or column,
                        auto determinantB = Matrix3x3<T>(iY, iZ, iW, kY, kZ, kW, lY, lZ, lW).Determinant();
                        // plus c times the determinant of the matrix that is not in c's row or column,
                        auto determinantC = Matrix3x3<T>(iY, iZ, iW, jY, jZ, jW, lY, lZ, lW).Determinant();
                        // minus d times the determinant of the matrix that is not in d's row or column,
                        auto determinantD = Matrix3x3<T>(iY, iZ, iW, jY, jZ, jW, kY, kZ, kW).Determinant();

                        return (iX * determinantA) - (jX * determinantB) + (kX * determinantC) - (lX * determinantD);
                    }

                    T* Data()
                    {
                        return &iX;
                    }

                    /// Reset to Identity
                    void Reset()
                    {
                        iX = static_cast<T>(1); jX = static_cast<T>(0); kX = static_cast<T>(0); lX = static_cast<T>(0);
                        iY = static_cast<T>(0); jY = static_cast<T>(1); kY = static_cast<T>(0); lY = static_cast<T>(0);
                        iZ = static_cast<T>(0); jZ = static_cast<T>(0); kZ = static_cast<T>(1); lZ = static_cast<T>(0);
                        iW = static_cast<T>(0); jW = static_cast<T>(0); kW = static_cast<T>(0); lW = static_cast<T>(1);
                    }

                    Vector3<T> Transform(const Vector3<T>& input) const
                    {
                        float w = 0.0f;

                        auto outputX = (iX * input.x) + (jX * input.y) + (kX * input.z) + (lX * w);
                        auto outputY = (iY * input.x) + (jY * input.y) + (kY * input.z) + (lY * w);
                        auto outputZ = (iZ * input.x) + (jZ * input.y) + (kZ * input.z) + (lZ * w);

                        return { outputX, outputY, outputZ };
                    }

                public:
                    friend Matrix4x4<T> operator*(const Matrix4x4<T>& left, const Matrix4x4<T>& right) {
                        return {
                            (left.iX * right.iX) + (left.iY * right.jX) + (left.iZ * right.kX) + (left.iW * right.lX),
                            (left.iX * right.iY) + (left.iY * right.jY) + (left.iZ * right.kY) + (left.iW * right.lY),
                            (left.iX * right.iZ) + (left.iY * right.jZ) + (left.iZ * right.kZ) + (left.iW * right.lZ),
                            (left.iX * right.iW) + (left.iY * right.jW) + (left.iZ * right.kW) + (left.iW * right.lW),

                            (left.jX * right.iX) + (left.jY * right.jX) + (left.jZ * right.kX) + (left.jW * right.lX),
                            (left.jX * right.iY) + (left.jY * right.jY) + (left.jZ * right.kY) + (left.jW * right.lY),
                            (left.jX * right.iZ) + (left.jY * right.jZ) + (left.jZ * right.kZ) + (left.jW * right.lZ),
                            (left.jX * right.iW) + (left.jY * right.jW) + (left.jZ * right.kW) + (left.jW * right.lW),

                            (left.kX * right.iX) + (left.kY * right.jX) + (left.kZ * right.kX) + (left.kW * right.lX),
                            (left.kX * right.iY) + (left.kY * right.jY) + (left.kZ * right.kY) + (left.kW * right.lY),
                            (left.kX * right.iZ) + (left.kY * right.jZ) + (left.kZ * right.kZ) + (left.kW * right.lZ),
                            (left.kX * right.iW) + (left.kY * right.jW) + (left.kZ * right.kW) + (left.kW * right.lW),

                            (left.lX * right.iX) + (left.lY * right.jX) + (left.lZ * right.kX) + (left.lW * right.lX),
                            (left.lX * right.iY) + (left.lY * right.jY) + (left.lZ * right.kY) + (left.lW * right.lY),
                            (left.lX * right.iZ) + (left.lY * right.jZ) + (left.lZ * right.kZ) + (left.lW * right.lZ),
                            (left.lX * right.iW) + (left.lY * right.jW) + (left.lZ * right.kW) + (left.lW * right.lW)
                        };
                    }

                    friend Matrix4x4<T> operator*(const Matrix4x4<T>& matrix, T factor) {
                        return {
                            matrix.iX * factor, matrix.iY * factor, matrix.iZ * factor, matrix.iW * factor,
                            matrix.jX * factor, matrix.jY * factor, matrix.jZ * factor, matrix.jW * factor,
                            matrix.kX * factor, matrix.kY * factor, matrix.kZ * factor, matrix.kW * factor,
                            matrix.lX * factor, matrix.lY * factor, matrix.lZ * factor, matrix.lW * factor
                        };
                    }
                };

                template <>
                class Matrix4x4<float>
                {
                public:
                    Matrix4x4(
                        float vectorIx = 1.0f, float vectorIy = 0.0f, float vectorIz = 0.0f, float vectorIw = 0.0f,
                        float vectorJx = 0.0f, float vectorJy = 1.0f, float vectorJz = 0.0f, float vectorJw = 0.0f,
                        float vectorKx = 0.0f, float vectorKy = 0.0f, float vectorKz = 1.0f, float vectorKw = 0.0f,
                        float vectorLx = 0.0f, float vectorLy = 0.0f, float vectorLz = 0.0f, float vectorLw = 1.0f)
                        : iX(vectorIx), jX(vectorJx), kX(vectorKx), lX(vectorLx)
                        , iY(vectorIy), jY(vectorJy), kY(vectorKy), lY(vectorLy)
                        , iZ(vectorIz), jZ(vectorJz), kZ(vectorKz), lZ(vectorLz)
                        , iW(vectorIw), jW(vectorJw), kW(vectorKw), lW(vectorLw)
                    {
                    }

                    Matrix4x4(const Vector4<float>& vectorI, const Vector4<float>& vectorJ, const Vector4<float>& vectorK, const Vector4<float>& vectorL)
                        : iX(vectorI.x), jX(vectorJ.x), kX(vectorK.x), lX(vectorL.x)
                        , iY(vectorI.y), jY(vectorJ.y), kY(vectorK.y), lY(vectorL.y)
                        , iZ(vectorI.z), jZ(vectorJ.z), kZ(vectorK.z), lZ(vectorL.z)
                        , iW(vectorI.w), jW(vectorJ.w), kW(vectorK.w), lW(vectorL.w)
                    {
                    }

                    float iX, jX, kX, lX;
                    float iY, jY, kY, lY;
                    float iZ, jZ, kZ, lZ;
                    float iW, jW, kW, lW;

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
                        auto determinantA = Matrix3x3<float>(jY, jZ, jW, kY, kZ, kW, lY, lZ, lW).Determinant();
                        // minus b times the determinant of the matrix that is not in b's row or column,
                        auto determinantB = Matrix3x3<float>(iY, iZ, iW, kY, kZ, kW, lY, lZ, lW).Determinant();
                        // plus c times the determinant of the matrix that is not in c's row or column,
                        auto determinantC = Matrix3x3<float>(iY, iZ, iW, jY, jZ, jW, lY, lZ, lW).Determinant();
                        // minus d times the determinant of the matrix that is not in d's row or column,
                        auto determinantD = Matrix3x3<float>(iY, iZ, iW, jY, jZ, jW, kY, kZ, kW).Determinant();

                        return (iX * determinantA) - (jX * determinantB) + (kX * determinantC) - (lX * determinantD);
                    }

                    float* Data()
                    {
                        return &iX;
                    }

                    void GetEulerAngles(float& pitchDegrees, float& yawDegrees, float& rollDegrees) const
                    {
                        pitchDegrees = MathsHelper::ArcSine(-kY);

                        if (MathsHelper::Cosine(pitchDegrees) == 0.0f) {
                            // Gimbal lock
                            yawDegrees = MathsHelper::ArcTangent(-iZ, iX);
                            rollDegrees = 0.0f;
                        }
                        else {
                            yawDegrees = MathsHelper::ArcTangent(kX, kZ);
                            rollDegrees = MathsHelper::ArcTangent(iY, jY);
                        }

                        pitchDegrees = MathsHelper::RadiansToDegrees(pitchDegrees);
                        yawDegrees = MathsHelper::RadiansToDegrees(yawDegrees);
                        rollDegrees = MathsHelper::RadiansToDegrees(rollDegrees);
                    }

                    /// Reset to Identity
                    void Reset()
                    {
                        iX = 1.0f; jX = 0.0f; kX = 0.0f; lX = 0.0f;
                        iY = 0.0f; jY = 1.0f; kY = 0.0f; lY = 0.0f;
                        iZ = 0.0f; jZ = 0.0f; kZ = 1.0f; lZ = 0.0f;
                        iW = 0.0f; jW = 0.0f; kW = 0.0f; lW = 1.0f;
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

                    void RotateAboutAxis(float angleInRadians, const Vector3<float>& axis)
                    {
                        auto rotationMatrix = CreateFromRotationAboutAxis(angleInRadians, axis);
                        *this = *this * rotationMatrix;
                    }

                    void RotateWithPitchYawRoll(float pitchInRadians, float yawInRadians, float rollInRadians)
                    {
                        auto rotationMatrix = CreateFromRotationPitchYawRoll(pitchInRadians, yawInRadians, rollInRadians);
                        *this = *this * rotationMatrix;
                    }

                    Vector3<float> Transform(const Vector3<float>& input) const
                    {
                        float w = 0.0f;

                        auto outputX = (iX * input.x) + (jX * input.y) + (kX * input.z) + (lX * w);
                        auto outputY = (iY * input.x) + (jY * input.y) + (kY * input.z) + (lY * w);
                        auto outputZ = (iZ * input.x) + (jZ * input.y) + (kZ * input.z) + (lZ * w);

                        return { outputX, outputY, outputZ };
                    }

                public:                    
                    static Matrix3x3<float> Create3x3From(const Matrix4x4<float>& matrix)
                    {
                        return { 
                            matrix.iX, matrix.iY, matrix.iZ, 
                            matrix.jX, matrix.jY, matrix.jZ,
                            matrix.kX, matrix.kY, matrix.kZ
                        };
                    }

                    static Matrix4x4<float> CreateFromRotationAboutX(float angleInRadians)
                    {
                        float cos_theta = MathsHelper::Cosine(angleInRadians);
                        float sin_theta = MathsHelper::Sine(angleInRadians);

                        Matrix4x4<float> result;
                        result.iX = 1.0f; result.jX = 0.0f;      result.kX = 0.0f;
                        result.iY = 0.0f; result.jY = cos_theta; result.kY = -sin_theta;
                        result.iZ = 0.0f; result.jZ = sin_theta; result.kZ = cos_theta;

                        return result;
                    }

                    static Matrix4x4<float> CreateFromRotationAboutY(float angleInRadians)
                    {
                        float cos_theta = MathsHelper::Cosine(angleInRadians);
                        float sin_theta = MathsHelper::Sine(angleInRadians);

                        Matrix4x4<float> result;
                        result.iX = cos_theta;  result.jX = 0.0f; result.kX = sin_theta;
                        result.iY = 0.0f;       result.jY = 1.0f; result.kY = 0.0f;
                        result.iZ = -sin_theta; result.jZ = 0.0f; result.kZ = cos_theta;

                        return result;
                    }

                    static Matrix4x4<float> CreateFromRotationAboutZ(float angleInRadians)
                    {
                        float cos_theta = MathsHelper::Cosine(angleInRadians);
                        float sin_theta = MathsHelper::Sine(angleInRadians);

                        Matrix4x4<float> result;
                        result.iX = cos_theta; result.jX = -sin_theta; result.kX = 0.0f;
                        result.iY = sin_theta; result.jY = cos_theta;  result.kY = 0.0f;
                        result.iZ = 0.0f;      result.jZ = 0.0f;       result.kZ = 1.0f;

                        return result;
                    }

                    static Matrix4x4<float> CreateFromRotationAboutAxis(float angleInRadians, const Vector3<float>& axis)
                    {
                        float cos_theta = MathsHelper::Cosine(angleInRadians);
                        float sin_theta = MathsHelper::Sine(angleInRadians);
                        float one_minus_cos_theta = 1.0f - cos_theta;

                        Matrix4x4<float> result;
                        result.iX = axis.x * axis.x * one_minus_cos_theta + cos_theta;
                        result.jX = axis.x * axis.y * one_minus_cos_theta - axis.z * sin_theta;
                        result.kX = axis.x * axis.z * one_minus_cos_theta + axis.y * sin_theta;
                        result.iY = axis.x * axis.y * one_minus_cos_theta + axis.z * sin_theta;
                        result.jY = axis.y * axis.y * one_minus_cos_theta + cos_theta;
                        result.kY = axis.y * axis.z * one_minus_cos_theta - axis.x * sin_theta;
                        result.iZ = axis.x * axis.z * one_minus_cos_theta - axis.y * sin_theta;
                        result.jZ = axis.y * axis.z * one_minus_cos_theta + axis.x * sin_theta;
                        result.kZ = axis.z * axis.z * one_minus_cos_theta + cos_theta;

                        return result;
                    }

                    static Matrix4x4<float> CreateFromRotationAxes(const Vector3<float>& xAxis, const Vector3<float>& yAxis, const Vector3<float>& zAxis)
                    {
                        Matrix4x4<float> result;
                        result.iX = xAxis.x;	result.jX = yAxis.x;	result.kX = zAxis.x;	result.lX = 0.0f;
                        result.iY = xAxis.y;	result.jY = yAxis.y;	result.kY = zAxis.y;	result.lY = 0.0f;
                        result.iZ = xAxis.z;	result.jZ = yAxis.z;	result.kZ = zAxis.z;	result.lZ = 0.0f;
                        result.iW = 0.0f;     result.jW = 0.0f;     result.kW = 0.0f;     result.lW = 1.0f;

                        return result;
                    }

                    static Matrix4x4<float> CreateFromRotationPitchYawRoll(float pitchRadians, float yawRadians, float rollRadians)
                    {
                        // Roll then Pitch then Yaw
                        auto cos_pitch = MathsHelper::Cosine(pitchRadians);
                        auto sin_pitch = MathsHelper::Sine(pitchRadians);
                        auto cos_yaw = MathsHelper::Cosine(yawRadians);
                        auto sin_yaw = MathsHelper::Sine(yawRadians);
                        auto cos_roll = MathsHelper::Cosine(rollRadians);
                        auto sin_roll = MathsHelper::Sine(rollRadians);

                        Matrix4x4<float> result;
                        result.iX = (cos_yaw * cos_roll) + (sin_yaw * sin_pitch * sin_roll);
                        result.jX = -(cos_yaw * sin_roll) + (sin_yaw * sin_pitch * cos_roll);
                        result.kX = sin_yaw * cos_pitch;
                        result.iY = sin_roll * cos_pitch;
                        result.jY = cos_roll * cos_pitch;
                        result.kY = -sin_pitch;
                        result.iZ = -(sin_yaw * cos_roll) + (cos_yaw * sin_pitch * sin_roll);
                        result.jZ = (sin_roll * sin_yaw) + (cos_yaw * sin_pitch * cos_roll);
                        result.kZ = cos_yaw * cos_pitch;

                        return result;
                    }

                    static Matrix4x4<float> CreateFromScale(const Vector3<float>& scale)
                    {
                        Matrix4x4<float> result;
                        result.iX = scale.x;
                        result.jY = scale.y;
                        result.kZ = scale.z;

                        return result;
                    }

                    static Matrix4x4<float> CreateFromTranslation(float x, float y, float z)
                    {
                        Matrix4x4<float> result;
                        result.lX = x;
                        result.lY = y;
                        result.lZ = z;

                        return result;
                    }

                    static Matrix4x4<float> CreateFromTranslation(const Vector3<float>& translation)
                    {
                        return CreateFromTranslation(translation.x, translation.y, translation.z);
                    }

                    static Matrix4x4<float> CreateOrthographic(float left, float right, float bottom, float top, float near, float far)
                    {
                        auto horizontal_zoom = 2.0f / (right - left);
                        auto vertical_zoom = 2.0f / (top - bottom);

                        auto i = Vector4<float>(horizontal_zoom, 0.0f, 0.0f, 0.0f);
                        auto j = Vector4<float>(0.0f, vertical_zoom, 0.0f, 0.0f);
                        auto k = Vector4<float>(0.0f, 0.0f, -2.0f / (far - near), 0.0f);
                        auto l = Vector4<float>(0.0f, 0.0f, -((near + far) / (far - near)), 1.0f);

                        return { i, j, k, l };
                    }

                    static Matrix4x4<float> CreateInverseOf(const Matrix4x4<float>& matrix)
                    {
                        Matrix4x4<float> result;

                        // Check it's not a singular matrix which has no inverse
                        if (matrix.Determinant() != 0.0f) 
                        {
                            auto cofactorMatrix = Create3x3From(matrix).Cofactor();
                            // Get the cofactor for each element in the 3x3 matrix and transpose
                            // Invert the translation elements
                            result.iX = cofactorMatrix.iX; result.jX = cofactorMatrix.iY; result.kX = cofactorMatrix.iZ; result.lX = -matrix.lX;
                            result.iY = cofactorMatrix.jX; result.jY = cofactorMatrix.jY; result.kY = cofactorMatrix.jZ; result.lY = -matrix.lY;
                            result.iZ = cofactorMatrix.kX; result.jZ = cofactorMatrix.kY; result.kZ = cofactorMatrix.kZ; result.lZ = -matrix.lZ;
                        }

                        return result;
                    }

                    static Matrix4x4<float> CreatePerspective(float horizontalFieldOfView, float aspectRatio, float near, float far)
                    {
                        float horizontal_zoom = 1.0f / MathsHelper::Tangent(horizontalFieldOfView / 2.0f);
                        float vertical_zoom = horizontal_zoom / aspectRatio;

                        auto i = Vector4<float>(horizontal_zoom, 0.0f, 0.0f, 0.0f);
                        auto j = Vector4<float>(0.0f, vertical_zoom, 0.0f, 0.0f);
                        auto k = Vector4<float>(0.0f, 0.0f, -((far + near) / (far - near)), -1.0f);
                        auto l = Vector4<float>(0.0f, 0.0f, (-2.0f * near * far) / (far - near), 0.0f);

                        return { i, j, k, l };
                    }

                public:
                    friend Matrix4x4<float> operator*(const Matrix4x4<float>& left, const Matrix4x4<float>& right) {
                        return {
                            (left.iX * right.iX) + (left.iY * right.jX) + (left.iZ * right.kX) + (left.iW * right.lX),
                            (left.iX * right.iY) + (left.iY * right.jY) + (left.iZ * right.kY) + (left.iW * right.lY),
                            (left.iX * right.iZ) + (left.iY * right.jZ) + (left.iZ * right.kZ) + (left.iW * right.lZ),
                            (left.iX * right.iW) + (left.iY * right.jW) + (left.iZ * right.kW) + (left.iW * right.lW),

                            (left.jX * right.iX) + (left.jY * right.jX) + (left.jZ * right.kX) + (left.jW * right.lX),
                            (left.jX * right.iY) + (left.jY * right.jY) + (left.jZ * right.kY) + (left.jW * right.lY),
                            (left.jX * right.iZ) + (left.jY * right.jZ) + (left.jZ * right.kZ) + (left.jW * right.lZ),
                            (left.jX * right.iW) + (left.jY * right.jW) + (left.jZ * right.kW) + (left.jW * right.lW),

                            (left.kX * right.iX) + (left.kY * right.jX) + (left.kZ * right.kX) + (left.kW * right.lX),
                            (left.kX * right.iY) + (left.kY * right.jY) + (left.kZ * right.kY) + (left.kW * right.lY),
                            (left.kX * right.iZ) + (left.kY * right.jZ) + (left.kZ * right.kZ) + (left.kW * right.lZ),
                            (left.kX * right.iW) + (left.kY * right.jW) + (left.kZ * right.kW) + (left.kW * right.lW),

                            (left.lX * right.iX) + (left.lY * right.jX) + (left.lZ * right.kX) + (left.lW * right.lX),
                            (left.lX * right.iY) + (left.lY * right.jY) + (left.lZ * right.kY) + (left.lW * right.lY),
                            (left.lX * right.iZ) + (left.lY * right.jZ) + (left.lZ * right.kZ) + (left.lW * right.lZ),
                            (left.lX * right.iW) + (left.lY * right.jW) + (left.lZ * right.kW) + (left.lW * right.lW)
                        };
                    }

                    friend Matrix4x4<float> operator*(const Matrix4x4<float>& matrix, float factor) {
                        return {
                            matrix.iX * factor, matrix.iY * factor, matrix.iZ * factor, matrix.iW * factor,
                            matrix.jX * factor, matrix.jY * factor, matrix.jZ * factor, matrix.jW * factor,
                            matrix.kX * factor, matrix.kY * factor, matrix.kZ * factor, matrix.kW * factor,
                            matrix.lX * factor, matrix.lY * factor, matrix.lZ * factor, matrix.lW * factor
                        };
                    }
                };
            }
        }
    }
}