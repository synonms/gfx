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
                template <typename T>
                class Matrix2x2
                {
                public:
                    Matrix2x2(T vectorIx = static_cast<T>(1), T vectorIy = static_cast<T>(0), T vectorJx = static_cast<T>(0), T vectorJy = static_cast<T>(1))
                        : iX(vectorIx), jX(vectorJx)
                        , iY(vectorIy), jY(vectorJy)
                    {
                    }

                    Matrix2x2(const Vector2<T>& vectorI, const Vector2<T>& vectorJ)
                        : iX(vectorI.x), jX(vectorJ.x)
                        , iY(vectorI.y), jY(vectorJ.y)
                    {
                    }

                    T iX, jX;
                    T iY, jY;

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
                        return (iX * jY) - (jX * iY);
                    }

                    /// Composition is the multiplication of two transforms and is read right to left
                    /// i.i [matrixA][matrixB] means that matrixB is applied first and then matrixA, which is coded matrixB.Multiply(matrixA)
                    /// [matrixA][matrixB][matrixC] would be matrixC.Multiply(matrixB).Multiply(matrixA)
                    Matrix2x2<T> Multiply(Matrix2x2<T> secondTransform)
                    {
                        return *this * secondTransform;
                    }

                    /// Reset to Identity
                    void Reset()
                    {
                        iX = static_cast<T>(1); jX = static_cast<T>(0);
                        iY = static_cast<T>(0); jY = static_cast<T>(1);
                    }

                    Vector2<T> Transform(const Vector2<T>& input) const
                    {
                        auto outputX = (iX * input.x) + (jX * input.y);
                        auto outputY = (iY * input.x) + (jY * input.y);

                        return { outputX, outputY };
                    }

                public:
                    static Matrix2x2<T> CreateFromScale(T xFactor, T yFactor)
                    {
                        return { xFactor, 0, 0, yFactor };
                    }

                public:
                    friend Matrix2x2<T> operator*(const Matrix2x2<T>& left, const Matrix2x2<T>& right) {
                        return {
                            (left.iX * right.iX) + (left.iY * right.jX),
                            (left.iX * right.iY) + (left.iY * right.jY),
                            (left.jX * right.iX) + (left.jY * right.jX),
                            (left.jX * right.iY) + (left.jY * right.jY)
                        };
                    }

                    friend Matrix2x2<T> operator*(const Matrix2x2<T>& matrix, T factor) {
                        return {
                            matrix.iX * factor, matrix.iY * factor,
                            matrix.jX * factor, matrix.jY * factor
                        };
                    }
                };
            }
        }
    }
}