#pragma once

#include <gfx\mathematics\linear\vector2.h>

namespace synonms
{
    namespace gfx
    {
        namespace mathematics
        {
            namespace linear
            {
                /// Given two basis vectors I (1.0, 0.0) and J (0.0, 1.0), 
                /// a 2x2 matrix represents a linear transformation by holding the resulting positions of I and J:
                ///   I J
                /// [ x x ]
                /// [ y y ]
                /// e.g. the matrix
                /// [ 2 0 ]
                /// [ 0 2 ]
                /// represents scaling by factor 2, as I is transformed from (1, 0) to (2, 0) and J from (0, 1) to (0, 2)
                /// An input vector of (3, 2) would be transfornmed to (6, 4) by this matrix
                class Matrix2x2
                {
                public:
                    Matrix2x2(float xAxisX = 1.0f, float xAxisY = 0.0f, float yAxisX = 0.0f, float yAxisY = 1.0f)
                        : xAxis(xAxisX, xAxisY)
                        , yAxis(yAxisX, yAxisY)
                    {
                    }

                    Matrix2x2(const Vector2<float>& xAxis, const Vector2<float>& yAxis)
                        : xAxis(xAxis)
                        , yAxis(yAxis)
                    {
                    }

                    Vector2<float> xAxis;
                    Vector2<float> yAxis;

                public:
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
                        return (xAxis.x * yAxis.y) - (yAxis.x * xAxis.y);
                    }

                    /// Composition is the multiplication of two transforms and is read right to left
                    /// i.i [matrixA][matrixB] means that matrixB is applied first and then matrixA, which is coded matrixB.Multiply(matrixA)
                    /// [matrixA][matrixB][matrixC] would be matrixC.Multiply(matrixB).Multiply(matrixA)
                    Matrix2x2 Multiply(const Matrix2x2& secondTransform)
                    {
                        return *this * secondTransform;
                    }

                    /// Reset to Identity
                    void Reset()
                    {
                        xAxis.x = 1.0f; yAxis.x = 0.0f;
                        xAxis.y = 0.0f; yAxis.y = 1.0f;
                    }

                    Vector2<float> Transform(const Vector2<float>& input) const
                    {
                        auto outputX = (xAxis.x * input.x) + (yAxis.x * input.y);
                        auto outputY = (xAxis.y * input.x) + (yAxis.y * input.y);

                        return { outputX, outputY };
                    }

                public:
                    static Matrix2x2 CreateFromScale(float xFactor, float yFactor)
                    {
                        return { 
                            xFactor, 0, 
                            0,       yFactor };
                    }

                public:
                    friend Matrix2x2 operator*(const Matrix2x2& left, const Matrix2x2& right) {
                        return {
                            (left.xAxis.x * right.xAxis.x) + (left.xAxis.y * right.yAxis.x),
                            (left.xAxis.x * right.xAxis.y) + (left.xAxis.y * right.yAxis.y),
                            (left.yAxis.x * right.xAxis.x) + (left.yAxis.y * right.yAxis.x),
                            (left.yAxis.x * right.xAxis.y) + (left.yAxis.y * right.yAxis.y)
                        };
                    }

                    friend Matrix2x2 operator*(const Matrix2x2& matrix, float factor) {
                        return {
                            matrix.xAxis.x * factor, matrix.xAxis.y * factor,
                            matrix.yAxis.x* factor,  matrix.yAxis.y* factor
                        };
                    }
                };
            }
        }
    }
}