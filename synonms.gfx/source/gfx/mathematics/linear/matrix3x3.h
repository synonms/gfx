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
                        T vectorIx = static_cast<T>(1), T vectorIy = static_cast<T>(0), T vectorIz = static_cast<T>(0),
                        T vectorJx = static_cast<T>(0), T vectorJy = static_cast<T>(1), T vectorJz = static_cast<T>(0),
                        T vectorKx = static_cast<T>(0), T vectorKy = static_cast<T>(0), T vectorKz = static_cast<T>(1))
                        : iX(vectorIx), jX(vectorJx), kX(vectorKx)
                        , iY(vectorIy), jY(vectorJy), kY(vectorKy)
                        , iZ(vectorIz), jZ(vectorJz), kZ(vectorKz)
                    {
                    }


                    Matrix3x3(const Vector3<T>& vectorI, const Vector3<T>& vectorJ, const Vector3<T>& vectorK)
                        : iX(vectorI.x), jX(vectorJ.x), kX(vectorK.x)
                        , iY(vectorI.y), jY(vectorJ.y), kY(vectorK.y)
                        , iZ(vectorI.z), jZ(vectorJ.z), kZ(vectorK.z)
                    {
                    }

                    T iX, jX, kX;
                    T iY, jY, kY;
                    T iZ, jZ, kZ;

                public:
                    Matrix3x3<T> Cofactor() const
                    {
                        auto i = Vector3<float>((jY * kZ) - (kY * jZ), (jX * kZ) - (kX * jZ), (jX * kY) - (kX * jY));
                        auto j = Vector3<float>((iY * kZ) - (kY * iZ), (iX * kZ) - (kX * iZ), (iX * kY) - (kX * iY));
                        auto k = Vector3<float>((iY * jZ) - (jY * iZ), (iX * jZ) - (jX * iZ), (iX * jY) - (jX * iY));

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
                        auto determinantA = Matrix2x2<T>(jY, jZ, kY, kZ).Determinant();
                        auto determinantB = Matrix2x2<T>(iY, iZ, kY, kZ).Determinant();
                        auto determinantC = Matrix2x2<T>(iY, iZ, jY, jZ).Determinant();

                        return (iX * determinantA) - (jX * determinantB) + (kX * determinantC);
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
                        iX = static_cast<T>(1); jX = static_cast<T>(0); kX = static_cast<T>(0);
                        iY = static_cast<T>(0); jY = static_cast<T>(1); kY = static_cast<T>(0);
                        iZ = static_cast<T>(0); jZ = static_cast<T>(0); kZ = static_cast<T>(1);
                    }

                    Vector3<T> Transform(const Vector3<T>& input) const
                    {
                        auto outputX = (iX * input.x) + (jX * input.y) + (kX * input.z);
                        auto outputY = (iY * input.x) + (jY * input.y) + (kY * input.z);
                        auto outputZ = (iZ * input.x) + (jZ * input.y) + (kZ * input.z);

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
                            (left.iX * right.iX) + (left.iY * right.jX) + (left.iZ * right.kX),
                            (left.iX * right.iY) + (left.iY * right.jY) + (left.iZ * right.kY),
                            (left.iX * right.iZ) + (left.iY * right.jZ) + (left.iZ * right.kZ),
                            (left.jX * right.iX) + (left.jY * right.jX) + (left.jZ * right.kX),
                            (left.jX * right.iY) + (left.jY * right.jY) + (left.jZ * right.kY),
                            (left.jX * right.iZ) + (left.jY * right.jZ) + (left.jZ * right.kZ),
                            (left.kX * right.iX) + (left.kY * right.jX) + (left.kZ * right.kX),
                            (left.kX * right.iY) + (left.kY * right.jY) + (left.kZ * right.kY),
                            (left.kX * right.iZ) + (left.kY * right.jZ) + (left.kZ * right.kZ)
                        };
                    }

                    friend Matrix3x3<T> operator*(const Matrix3x3<T>& matrix, T factor) {
                        return {
                            matrix.iX * factor, matrix.iY * factor, matrix.iZ * factor,
                            matrix.jX * factor, matrix.jY * factor, matrix.jZ * factor,
                            matrix.kX * factor, matrix.kY * factor, matrix.kZ * factor
                        };
                    }
                };
            }
        }
    }
}