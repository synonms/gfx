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

                    Vector4<T> GetIColumn() const
                    {
                        return { iX, iY, iZ, iW };
                    }

                    Vector4<T> GetJColumn() const
                    {
                        return { jX, jY, jZ, jW };
                    }

                    Vector4<T> GetKColumn() const
                    {
                        return { kX, kY, kZ, kW };
                    }

                    Vector4<T> GetLColumn() const
                    {
                        return { lX, lY, lZ, lW };
                    }

                    Vector4<T> GetXRow() const
                    {
                        return { iX, jX, kX, lX };
                    }

                    Vector4<T> GetYRow() const
                    {
                        return { iY, jY, kY, lY };
                    }

                    Vector4<T> GetZRow() const
                    {
                        return { iZ, jZ, kZ, lZ };
                    }

                    Vector4<T> GetWRow() const
                    {
                        return { iW, jW, kW, lW };
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
                    //Matrix4x4(
                    //    float vectorIx = 1.0f, float vectorIy = 0.0f, float vectorIz = 0.0f, float vectorIw = 0.0f,
                    //    float vectorJx = 0.0f, float vectorJy = 1.0f, float vectorJz = 0.0f, float vectorJw = 0.0f,
                    //    float vectorKx = 0.0f, float vectorKy = 0.0f, float vectorKz = 1.0f, float vectorKw = 0.0f,
                    //    float vectorLx = 0.0f, float vectorLy = 0.0f, float vectorLz = 0.0f, float vectorLw = 1.0f)
                    //    : iX(vectorIx), jX(vectorJx), kX(vectorKx), lX(vectorLx)
                    //    , iY(vectorIy), jY(vectorJy), kY(vectorKy), lY(vectorLy)
                    //    , iZ(vectorIz), jZ(vectorJz), kZ(vectorKz), lZ(vectorLz)
                    //    , iW(vectorIw), jW(vectorJw), kW(vectorKw), lW(vectorLw)
                    //{
                    //}

                    //Matrix4x4(const Vector4<float>& vectorI, const Vector4<float>& vectorJ, const Vector4<float>& vectorK, const Vector4<float>& vectorL)
                    //    : iX(vectorI.x), jX(vectorJ.x), kX(vectorK.x), lX(vectorL.x)
                    //    , iY(vectorI.y), jY(vectorJ.y), kY(vectorK.y), lY(vectorL.y)
                    //    , iZ(vectorI.z), jZ(vectorJ.z), kZ(vectorK.z), lZ(vectorL.z)
                    //    , iW(vectorI.w), jW(vectorJ.w), kW(vectorK.w), lW(vectorL.w)
                    //{
                    //}

                    //float iX, jX, kX, lX;
                    //float iY, jY, kY, lY;
                    //float iZ, jZ, kZ, lZ;
                    //float iW, jW, kW, lW;


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

                    Matrix4x4(const Vector4<float>& xAxis, const Vector4<float>& yAxis, const Vector4<float>& zAxis, const Vector4<float>& origin)
                        : xAxis(xAxis)
                        , yAxis(yAxis)
                        , zAxis(zAxis)
                        , origin(origin)
                    {
                    }

                    ///  X axis Y axis Z axis
                    /// [scaleX 0      0      translationX]
                    /// [0      scaleY 0      translationY]
                    /// [0      0      scaleZ translationZ]
                    /// [0      0      0      1           ]
                    Vector4<float> xAxis;
                    Vector4<float> yAxis;
                    Vector4<float> zAxis;
                    Vector4<float> origin;

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
                        auto determinantA = Matrix3x3<float>(
                            yAxis.y,  yAxis.z,  yAxis.w, 
                            zAxis.y,  zAxis.z,  zAxis.w, 
                            origin.y, origin.z, origin.w)
                            .Determinant();
                        // minus b times the determinant of the matrix that is not in b's row or column,
                        auto determinantB = Matrix3x3<float>(
                            xAxis.y,  xAxis.z,  xAxis.w, 
                            zAxis.y,  zAxis.z,  zAxis.w, 
                            origin.y, origin.z, origin.w)
                            .Determinant();
                        // plus c times the determinant of the matrix that is not in c's row or column,
                        auto determinantC = Matrix3x3<float>(
                            xAxis.y,  xAxis.z,  xAxis.w, 
                            yAxis.y,  yAxis.z,  yAxis.w, 
                            origin.y, origin.z, origin.w)
                            .Determinant();
                        // minus d times the determinant of the matrix that is not in d's row or column,
                        auto determinantD = Matrix3x3<float>(
                            xAxis.y, xAxis.z, xAxis.w, 
                            yAxis.y, yAxis.z, yAxis.w, 
                            zAxis.y, zAxis.z, zAxis.w)
                            .Determinant();

                        return (xAxis.x * determinantA) - (yAxis.x * determinantB) + (zAxis.x * determinantC) - (origin.x * determinantD);
                    }

                    float* Data()
                    {
                        return &xAxis.x;
                    }

                    void GetEulerAngles(float& pitchDegrees, float& yawDegrees, float& rollDegrees) const
                    {
                        pitchDegrees = MathsHelper::ArcSine(-zAxis.y);

                        if (MathsHelper::Cosine(pitchDegrees) == 0.0f) {
                            // Gimbal lock
                            yawDegrees = MathsHelper::ArcTangent(-xAxis.z, xAxis.x);
                            rollDegrees = 0.0f;
                        }
                        else {
                            yawDegrees = MathsHelper::ArcTangent(yAxis.x, yAxis.z);
                            rollDegrees = MathsHelper::ArcTangent(xAxis.y, yAxis.y);
                        }

                        pitchDegrees = MathsHelper::RadiansToDegrees(pitchDegrees);
                        yawDegrees = MathsHelper::RadiansToDegrees(yawDegrees);
                        rollDegrees = MathsHelper::RadiansToDegrees(rollDegrees);
                    }

                    Vector4<float> GetXRow() const
                    {
                        return { xAxis.x, yAxis.x, zAxis.x, origin.x };
                    }

                    Vector4<float> GetYRow() const
                    {
                        return { xAxis.y, yAxis.y, zAxis.y, origin.y };
                    }

                    Vector4<float> GetZRow() const
                    {
                        return { xAxis.z, yAxis.z, zAxis.z, origin.z };
                    }

                    Vector4<float> GetWRow() const
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

                        auto outputX = (xAxis.x * input.x) + (yAxis.x * input.y) + (zAxis.x * input.z) + (origin.x * w);
                        auto outputY = (xAxis.y * input.x) + (yAxis.y * input.y) + (zAxis.y * input.z) + (origin.y * w);
                        auto outputZ = (xAxis.z * input.x) + (yAxis.z * input.y) + (zAxis.z * input.z) + (origin.z * w);

                        return { outputX, outputY, outputZ };
                    }

                public:
                    static Matrix3x3<float> Create3x3From(const Matrix4x4<float>& matrix)
                    {
                        return { 
                            matrix.xAxis.x, matrix.xAxis.y, matrix.xAxis.z,
                            matrix.yAxis.x, matrix.yAxis.y, matrix.yAxis.z,
                            matrix.zAxis.x, matrix.zAxis.y, matrix.zAxis.z
                        };
                    }

                    static Matrix4x4<float> CreateFromRotationAboutX(float angleInRadians)
                    {
                        float cos_theta = MathsHelper::Cosine(angleInRadians);
                        float sin_theta = MathsHelper::Sine(angleInRadians);

                        return {
                            1.0f, 0.0f,      0.0f,       0.0f,
                            0.0f, cos_theta, -sin_theta, 0.0f,
                            0.0f, sin_theta, cos_theta,  0.0f,
                            0.0f, 0.0f,      0.0f,       1.0f
                        };
                    }

                    static Matrix4x4<float> CreateFromRotationAboutY(float angleInRadians)
                    {
                        float cos_theta = MathsHelper::Cosine(angleInRadians);
                        float sin_theta = MathsHelper::Sine(angleInRadians);

                        return {
                            cos_theta,  0.0f, sin_theta, 0.0f,
                            0.0f,       1.0f, 0.0f,      0.0f,
                            -sin_theta, 0.0f, cos_theta, 0.0f,
                            0.0f,       0.0f, 0.0f,      1.0f
                        };
                    }

                    static Matrix4x4<float> CreateFromRotationAboutZ(float angleInRadians)
                    {
                        float cos_theta = MathsHelper::Cosine(angleInRadians);
                        float sin_theta = MathsHelper::Sine(angleInRadians);

                        return {
                            cos_theta, -sin_theta, 0.0f, 0.0f,
                            sin_theta, cos_theta,  0.0f, 0.0f,
                            0.0f,      0.0f,       1.0f, 0.0f,
                            0.0f,      0.0f,       0.0f, 1.0f
                        };
                    }

                    static Matrix4x4<float> CreateFromRotationAboutAxis(float angleInRadians, const Vector3<float>& axis)
                    {
                        float cos_theta = MathsHelper::Cosine(angleInRadians);
                        float sin_theta = MathsHelper::Sine(angleInRadians);
                        float one_minus_cos_theta = 1.0f - cos_theta;

                        Matrix4x4<float> result;
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

                    static Matrix4x4<float> CreateFromRotationAxes(const Vector3<float>& xAxis, const Vector3<float>& yAxis, const Vector3<float>& zAxis)
                    {
                        Matrix4x4<float> result;
                        result.xAxis.x = xAxis.x;	result.yAxis.x = yAxis.x;	result.zAxis.x = zAxis.x;	result.origin.x = 0.0f;
                        result.xAxis.y = xAxis.y;	result.yAxis.y = yAxis.y;	result.zAxis.y = zAxis.y;	result.origin.y = 0.0f;
                        result.xAxis.z = xAxis.z;	result.yAxis.z = yAxis.z;	result.zAxis.z = zAxis.z;	result.origin.z = 0.0f;
                        result.xAxis.w = 0.0f;      result.yAxis.w = 0.0f;      result.zAxis.w = 0.0f;      result.origin.w = 1.0f;

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

                    static Matrix4x4<float> CreateFromScale(const Vector3<float>& scale)
                    {
                        Matrix4x4<float> result;
                        result.xAxis.x = scale.x;
                        result.yAxis.y = scale.y;
                        result.zAxis.z = scale.z;

                        return result;
                    }

                    static Matrix4x4<float> CreateFromTranslation(float x, float y, float z)
                    {
                        Matrix4x4<float> result;
                        result.origin.x = x;
                        result.origin.y = y;
                        result.origin.z = z;
 
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
                            result.xAxis.x = cofactorMatrix.xAxis.x; result.yAxis.x = cofactorMatrix.xAxis.y; result.zAxis.x = cofactorMatrix.xAxis.z; result.origin.x = -matrix.origin.x;
                            result.xAxis.y = cofactorMatrix.yAxis.x; result.yAxis.y = cofactorMatrix.yAxis.y; result.zAxis.y = cofactorMatrix.yAxis.z; result.origin.y = -matrix.origin.y;
                            result.xAxis.z = cofactorMatrix.zAxis.x; result.yAxis.z = cofactorMatrix.zAxis.y; result.zAxis.z = cofactorMatrix.zAxis.z; result.origin.z = -matrix.origin.z;
                        }

                        return result;
                    }

                    static Matrix4x4<float> CreatePerspective(float horizontalFieldOfView, float aspectRatio, float near, float far)
                    {
                        float horizontal_zoom = 1.0f / MathsHelper::Tangent(horizontalFieldOfView / 2.0f);
                        float vertical_zoom = horizontal_zoom / aspectRatio;

                        return {
                            horizontal_zoom, 0.0f,          0.0f,                              0.0f,
                            0.0f,            vertical_zoom, 0.0f,                              0.0f,
                            0.0f,            0.0f,         -((far + near) / (far - near)),    -1.0f,
                            0.0f,            0.0f,        (-2.0f * near * far) / (far - near), 0.0f
                        };
                    }

                public:
                    friend Matrix4x4<float> operator*(const Matrix4x4<float>& left, const Matrix4x4<float>& right) {
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

                    friend Matrix4x4<float> operator*(const Matrix4x4<float>& matrix, float factor) {
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
}