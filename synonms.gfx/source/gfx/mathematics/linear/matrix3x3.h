#pragma once

#include <gfx\mathematics\linear\matrix2x2.h>
#include <gfx\mathematics\linear\vector3.h>

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
                class Matrix3x3
                {
                public:
                    Matrix3x3(
                        T xAxisX = static_cast<T>(1), T xAxisY = static_cast<T>(0), T xAxisZ = static_cast<T>(0),
                        T yAxisX = static_cast<T>(0), T yAxisY = static_cast<T>(1), T yAxisZ = static_cast<T>(0),
                        T zAxisX = static_cast<T>(0), T zAxisY = static_cast<T>(0), T zAxisZ = static_cast<T>(1))
                        : xAxis({xAxisX, xAxisY, xAxisZ})
                        , yAxis({yAxisX, yAxisY, yAxisZ})
                        , zAxis({zAxisX, zAxisY, zAxisZ})
                    {
                    }


                    Matrix3x3(const Vector3<T>& xAxis, const Vector3<T>& yAxis, const Vector3<T>& zAxis)
                        : xAxis(xAxis)
                        , yAxis(yAxis)
                        , zAxis(zAxis)
                    {
                    }

                    Vector3<T> xAxis;
                    Vector3<T> yAxis;
                    Vector3<T> zAxis;

                public:
                    Matrix3x3<T> Cofactor() const
                    {
                        auto i = Vector3<float>((yAxis.y * zAxis.z) - (zAxis.y * yAxis.z), (yAxis.x * zAxis.z) - (zAxis.x * yAxis.z), (yAxis.x * zAxis.y) - (zAxis.x * yAxis.y));
                        auto j = Vector3<float>((xAxis.y * zAxis.z) - (zAxis.y * xAxis.z), (xAxis.x * zAxis.z) - (zAxis.x * xAxis.z), (xAxis.x * zAxis.y) - (zAxis.x * xAxis.y));
                        auto k = Vector3<float>((xAxis.y * yAxis.z) - (yAxis.y * xAxis.z), (xAxis.x * yAxis.z) - (yAxis.x * xAxis.z), (xAxis.x * yAxis.y) - (yAxis.x * xAxis.y));

                        return {i, j, k};
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
                        auto determinantA = Matrix2x2<T>(yAxis.y, yAxis.z, zAxis.y, zAxis.z).Determinant();
                        auto determinantB = Matrix2x2<T>(xAxis.y, xAxis.z, zAxis.y, zAxis.z).Determinant();
                        auto determinantC = Matrix2x2<T>(xAxis.y, xAxis.z, yAxis.y, yAxis.z).Determinant();

                        return (xAxis.x * determinantA) - (yAxis.x * determinantB) + (zAxis.x * determinantC);
                    }

                    /// Composition is the multiplication of two transforms and is read right to left
                    /// i.i [matrixA][matrixB] means that matrixB is applied first and then matrixA, which is coded matrixB.Multiply(matrixA)
                    /// [matrixA][matrixB][matrixC] would be matrixC.Multiply(matrixB).Multiply(matrixA)
                    Matrix3x3<T> Multiply(const Matrix3x3<T>& other) const
                    {
                        return *this * other;
                    }

                    /// Reset to Identity
                    void Reset()
                    {
                        xAxis.x = static_cast<T>(1); yAxis.x = static_cast<T>(0); zAxis.x = static_cast<T>(0);
                        xAxis.y = static_cast<T>(0); yAxis.y = static_cast<T>(1); zAxis.y = static_cast<T>(0);
                        xAxis.z = static_cast<T>(0); yAxis.z = static_cast<T>(0); zAxis.z = static_cast<T>(1);
                    }

                    Vector3<T> Transform(const Vector3<T>& input) const
                    {
                        auto outputX = (xAxis.x * input.x) + (yAxis.x * input.y) + (zAxis.x * input.z);
                        auto outputY = (xAxis.y * input.x) + (yAxis.y * input.y) + (zAxis.y * input.z);
                        auto outputZ = (xAxis.z * input.x) + (yAxis.z * input.y) + (zAxis.z * input.z);

                        return { outputX, outputY, outputZ };
                    }

                public:
                    static Matrix3x3<T> CreateFromScale(T xFactor, T yFactor, T zFactor)
                    {
                        return { xFactor, 0, 0, 0, yFactor, 0, 0, 0, zFactor };
                    }

                public:
                    friend Matrix3x3<T> operator*(const Matrix3x3<T>& left, const Matrix3x3<T>& right) {
                        return {
                            (left.xAxis.x * right.xAxis.x) + (left.xAxis.y * right.yAxis.x) + (left.xAxis.z * right.kX),
                            (left.xAxis.x * right.xAxis.y) + (left.xAxis.y * right.yAxis.y) + (left.xAxis.z * right.kY),
                            (left.xAxis.x * right.xAxis.z) + (left.xAxis.y * right.yAxis.z) + (left.xAxis.z * right.kZ),
                            (left.yAxis.x * right.xAxis.x) + (left.yAxis.y * right.yAxis.x) + (left.yAxis.z * right.kX),
                            (left.yAxis.x * right.xAxis.y) + (left.yAxis.y * right.yAxis.y) + (left.yAxis.z * right.kY),
                            (left.yAxis.x * right.xAxis.z) + (left.yAxis.y * right.yAxis.z) + (left.yAxis.z * right.kZ),
                            (left.zAxis.x * right.xAxis.x) + (left.zAxis.y * right.yAxis.x) + (left.zAxis.z * right.kX),
                            (left.zAxis.x * right.xAxis.y) + (left.zAxis.y * right.yAxis.y) + (left.zAxis.z * right.kY),
                            (left.zAxis.x * right.xAxis.z) + (left.zAxis.y * right.yAxis.z) + (left.zAxis.z * right.kZ)
                        };
                    }

                    friend Matrix3x3<T> operator*(const Matrix3x3<T>& matrix, T factor) {
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
}