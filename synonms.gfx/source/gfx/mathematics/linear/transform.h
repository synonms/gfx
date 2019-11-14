#pragma once

#include <gfx\mathematics\linear\matrix4x4.h>
#include <gfx\mathematics\linear\vector3.h>

namespace synonms
{
    namespace gfx
    {
        namespace mathematics
        {
            namespace linear
            {
                class Transform
                {
                public:
                    enum class TransformBehaviour
                    {
                        FirstPerson,   // 5 DOF, all movement is in z plane
                        Flight         // 6 DOF
                    };

                    static const Vector3<float> WorldXAxis;
                    static const Vector3<float> WorldYAxis;
                    static const Vector3<float> WorldZAxis;

                public:
                    Transform(TransformBehaviour behaviour = TransformBehaviour::Flight);

                    TransformBehaviour behaviour;

                    Vector3<float> position{ 0.0f, 0.0f, 0.0f };
                    Vector3<float> rotationDegrees{ 0.0f, 0.0f, 0.0f };
                    Vector3<float> scale{ 1.0f, 1.0f, 1.0f };

                public:
                    //void LookAt(const Vector3<float>& target);
                    //void LookAt(const Vector3<float>& eye, const Vector3<float>& target, const Vector3<float>& up);
//                    void Rotate(float pitchInDegrees, float yawInDegrees, float rollInDegrees);
//                    void Scale(const Vector3<float>& scale);
//                    void Translate(float deltaX, float deltaY, float deltaZ);
//                    void TranslateAbsolute(const Vector3<float>& deltaTranslation);

                    Matrix4x4 GetModelMatrix() const;
                    Matrix3x3 GetNormalMatrix() const;
                    Matrix4x4 GetRotationMatrix() const;
                    Matrix4x4 GetScaleMatrix() const;
                    Matrix4x4 GetTranslationMatrix() const;
                    Matrix4x4 GetViewMatrix(bool isRotationOnly = false) const;	// For camera/viewpoint - use rotationOnly when applying to skyboxes

                    void Reset();

                private:

                    //                    Vector3<float> _viewDirection{ 0.0f, 0.0f, 1.0f };

//                    Vector3<float> _xAxis{ 1.0f, 0.0f, 0.0f };
//                    Vector3<float> _yAxis{ 0.0f, 1.0f, 0.0f };
//                    Vector3<float> _zAxis{ 0.0f, 0.0f, 1.0f };

                    //float _yawInDegrees{ 0 };
                    //float _pitchInDegrees{ 0 };
                    //float _rollInDegrees{ 0 };

//                    void RotateFlight(float pitchInDegrees, float yawInDegrees, float rollInDegrees);
//                    void RotateFirstPerson(float pitchInDegrees, float yawInDegrees);
//                    void SetXAxis(const Vector3<float>& x);
//                    void SetYAxis(const Vector3<float>& y);
//                    void SetZAxis(const Vector3<float>& z);
                };
            }
        }
    }
}