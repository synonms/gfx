#pragma once

#include <gfx\transforms\matrix2x2.h>
#include <gfx\geometry\vector3.h>

namespace synonms
{
    namespace gfx
    {
        namespace transforms
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
            class Matrix3x3
            {
            public:
                Matrix3x3(
                    float xAxisX = 1.0f, float xAxisY = 0.0f, float xAxisZ = 0.0f,
                    float yAxisX = 0.0f, float yAxisY = 1.0f, float yAxisZ = 0.0f,
                    float zAxisX = 0.0f, float zAxisY = 0.0f, float zAxisZ = 1.0f)
                    : xAxis({xAxisX, xAxisY, xAxisZ})
                    , yAxis({yAxisX, yAxisY, yAxisZ})
                    , zAxis({zAxisX, zAxisY, zAxisZ})
                {
                }


                Matrix3x3(const geometry::Vector3<float>& xAxis, const geometry::Vector3<float>& yAxis, const geometry::Vector3<float>& zAxis)
                    : xAxis(xAxis)
                    , yAxis(yAxis)
                    , zAxis(zAxis)
                {
                }

                geometry::Vector3<float> xAxis;
                geometry::Vector3<float> yAxis;
                geometry::Vector3<float> zAxis;

            public:
                /// Calculates the cofactor of each element in the matrix and puts the result in the same position
                Matrix3x3 Cofactor() const
                {
                    //auto i = Vector3<float>(
                    //    (yAxis.y * zAxis.z) - (zAxis.y * yAxis.z), 
                    //    (yAxis.x * zAxis.z) - (zAxis.x * yAxis.z), 
                    //    (yAxis.x * zAxis.y) - (zAxis.x * yAxis.y));
                    //auto j = Vector3<float>(
                    //    (xAxis.y * zAxis.z) - (zAxis.y * xAxis.z), 
                    //    (xAxis.x * zAxis.z) - (zAxis.x * xAxis.z), 
                    //    (xAxis.x * zAxis.y) - (zAxis.x * xAxis.y));
                    //auto k = Vector3<float>(
                    //    (xAxis.y * yAxis.z) - (yAxis.y * xAxis.z), 
                    //    (xAxis.x * yAxis.z) - (yAxis.x * xAxis.z), 
                    //    (xAxis.x * yAxis.y) - (yAxis.x * xAxis.y));

                    auto i = geometry::Vector3<float>(
                        (yAxis.y * zAxis.z) - (yAxis.z * zAxis.y),
                        (zAxis.y * xAxis.z) - (zAxis.z * xAxis.y),
                        (xAxis.y * yAxis.z) - (xAxis.z * yAxis.y));
                    auto j = geometry::Vector3<float>(
                        (yAxis.z * zAxis.x) - (yAxis.x * zAxis.z),
                        (xAxis.x * zAxis.z) - (xAxis.z * zAxis.x),
                        (xAxis.z * yAxis.x) - (xAxis.x * yAxis.z));
                    auto k = geometry::Vector3<float>(
                        (yAxis.x * zAxis.y) - (yAxis.y * zAxis.x),
                        (zAxis.x * xAxis.y) - (zAxis.y * xAxis.x),
                        (xAxis.x * yAxis.y) - (xAxis.y * yAxis.x));

                    return {i, j, k};
                }

                static Matrix3x3 CreateInverseOf(const Matrix3x3& matrix)
                {
                    float tmp[9];

                    tmp[0] = (matrix.yAxis.y * matrix.zAxis.z) - (matrix.yAxis.z * matrix.zAxis.y);
                    tmp[1] = (matrix.zAxis.y * matrix.xAxis.z) - (matrix.zAxis.z * matrix.xAxis.y);
                    tmp[2] = (matrix.xAxis.y * matrix.yAxis.z) - (matrix.xAxis.z * matrix.yAxis.y);
                    tmp[3] = (matrix.yAxis.z * matrix.zAxis.x) - (matrix.yAxis.x * matrix.zAxis.z);
                    tmp[4] = (matrix.xAxis.x * matrix.zAxis.z) - (matrix.xAxis.z * matrix.zAxis.x);
                    tmp[5] = (matrix.xAxis.z * matrix.yAxis.x) - (matrix.xAxis.x * matrix.yAxis.z);
                    tmp[6] = (matrix.yAxis.x * matrix.zAxis.y) - (matrix.yAxis.y * matrix.zAxis.x);
                    tmp[7] = (matrix.zAxis.x * matrix.xAxis.y) - (matrix.zAxis.y * matrix.xAxis.x);
                    tmp[8] = (matrix.xAxis.x * matrix.yAxis.y) - (matrix.xAxis.y * matrix.yAxis.x);

                    // check determinant if it is 0
                    auto determinant = matrix.xAxis.x * tmp[0] + matrix.xAxis.y * tmp[3] + matrix.xAxis.z * tmp[6];
                    if (mathematics::MathsHelper::Absolute(determinant) <= mathematics::epsilon)
                    {
                        return Matrix3x3(); // cannot invert, make it identity matrix
                    }

                    // divide by the determinant
                    auto invDeterminant = 1.0f / determinant;

                    return {
                        invDeterminant * tmp[0], invDeterminant * tmp[1], invDeterminant * tmp[2],
                        invDeterminant * tmp[3], invDeterminant * tmp[4], invDeterminant * tmp[5],
                        invDeterminant * tmp[6], invDeterminant * tmp[7], invDeterminant * tmp[8]
                    };
                }

                const float* Data() const
                {
                    return &xAxis.x;
                }

                /// Determinant is the factor by which the area/volume represented by the basis vectors is increased/decreased by the transform
                /// e.g. with the matrix
                /// [ 2 0 ]
                /// [ 0 2 ]
                /// the area increases from 1x1 to 2x2 so the Determinant is 4
                /// Negative Determinant means that the plane is flipped (orientation of space is inverted) for 2D
                /// For 3D it means that the coordinate system has flipped from right handed to left handed
                float Determinant() const
                {
                    auto determinantA = Matrix2x2(yAxis.y, yAxis.z, zAxis.y, zAxis.z).Determinant();
                    auto determinantB = Matrix2x2(xAxis.y, xAxis.z, zAxis.y, zAxis.z).Determinant();
                    auto determinantC = Matrix2x2(xAxis.y, xAxis.z, yAxis.y, yAxis.z).Determinant();

                    return (xAxis.x * determinantA) - (yAxis.x * determinantB) + (zAxis.x * determinantC);
                }

                /// Composition is the multiplication of two transforms and is read right to left
                /// i.i [matrixA][matrixB] means that matrixB is applied first and then matrixA, which is coded matrixB.Multiply(matrixA)
                /// [matrixA][matrixB][matrixC] would be matrixC.Multiply(matrixB).Multiply(matrixA)
                Matrix3x3 Multiply(const Matrix3x3& other) const
                {
                    return *this * other;
                }

                /// Reset to Identity
                void Reset()
                {
                    xAxis.x = 1.0f; yAxis.x = 0.0f; zAxis.x = 0.0f;
                    xAxis.y = 0.0f; yAxis.y = 1.0f; zAxis.y = 0.0f;
                    xAxis.z = 0.0f; yAxis.z = 0.0f; zAxis.z = 1.0f;
                }

                geometry::Vector3<float> Transform(const geometry::Vector3<float>& input) const
                {
                    auto outputX = (xAxis.x * input.x) + (yAxis.x * input.y) + (zAxis.x * input.z);
                    auto outputY = (xAxis.y * input.x) + (yAxis.y * input.y) + (zAxis.y * input.z);
                    auto outputZ = (xAxis.z * input.x) + (yAxis.z * input.y) + (zAxis.z * input.z);

                    return { outputX, outputY, outputZ };
                }


                    
            public:
                static Matrix3x3 CreateFromScale(float xFactor, float yFactor, float zFactor)
                {
                    return { 
                        xFactor, 0,       0, 
                        0,       yFactor, 0, 
                        0,       0,       zFactor
                    };
                }

                static Matrix3x3 CreateTransposeOf(const Matrix3x3& matrix)
                {
                    return {
                        matrix.xAxis.x, matrix.yAxis.x, matrix.zAxis.x,
                        matrix.xAxis.y, matrix.yAxis.y, matrix.zAxis.y,
                        matrix.xAxis.z, matrix.yAxis.z, matrix.zAxis.z
                    };
                }

            public:
                friend Matrix3x3 operator*(const Matrix3x3& left, const Matrix3x3& right) {
                    return {
                        (left.xAxis.x * right.xAxis.x) + (left.xAxis.y * right.yAxis.x) + (left.xAxis.z * right.zAxis.x),
                        (left.xAxis.x * right.xAxis.y) + (left.xAxis.y * right.yAxis.y) + (left.xAxis.z * right.zAxis.y),
                        (left.xAxis.x * right.xAxis.z) + (left.xAxis.y * right.yAxis.z) + (left.xAxis.z * right.zAxis.z),
                        (left.yAxis.x * right.xAxis.x) + (left.yAxis.y * right.yAxis.x) + (left.yAxis.z * right.zAxis.x),
                        (left.yAxis.x * right.xAxis.y) + (left.yAxis.y * right.yAxis.y) + (left.yAxis.z * right.zAxis.y),
                        (left.yAxis.x * right.xAxis.z) + (left.yAxis.y * right.yAxis.z) + (left.yAxis.z * right.zAxis.z),
                        (left.zAxis.x * right.xAxis.x) + (left.zAxis.y * right.yAxis.x) + (left.zAxis.z * right.zAxis.x),
                        (left.zAxis.x * right.xAxis.y) + (left.zAxis.y * right.yAxis.y) + (left.zAxis.z * right.zAxis.y),
                        (left.zAxis.x * right.xAxis.z) + (left.zAxis.y * right.yAxis.z) + (left.zAxis.z * right.zAxis.z)
                    };
                }

                friend Matrix3x3 operator*(const Matrix3x3& matrix, float factor) {
                    return {
                        matrix.xAxis.x * factor, matrix.xAxis.y * factor, matrix.xAxis.z * factor,
                        matrix.yAxis.x * factor, matrix.yAxis.y * factor, matrix.yAxis.z * factor,
                        matrix.zAxis.x * factor, matrix.zAxis.y * factor, matrix.zAxis.z * factor
                    };
                }
            };
        }
    }
}