#pragma once

#include <gfx\primitives\mesh.h>
#include <gfx\materials\material.h>
#include <gfx\mathematics\linear\matrix3x3.h>
#include <gfx\mathematics\linear\matrix4x4.h>

#include <string>

namespace synonms
{
    namespace gfx
    {
        namespace primitives
        {
            class MeshInstance
            {
            public:
                MeshInstance(const Mesh& mesh, const materials::Material& material)
                    : _mesh(mesh), _material(material)
                {}
                
                mathematics::linear::Vector3<float> position{ 0.0f, 0.0f, 0.0f };
                mathematics::linear::Vector3<float> rotationDegrees{ 0.0f, 0.0f, 0.0f };
                mathematics::linear::Vector3<float> scale{ 1.0f, 1.0f, 1.0f };

                inline const materials::Material& GetMaterial() const 
                { 
                    return _material; 
                }

                inline const Mesh& GetMesh() const 
                { 
                    return _mesh; 
                }

                inline mathematics::linear::Matrix4x4 GetModelMatrix() const 
                { 
                    return GetTranslationMatrix() * (GetRotationMatrix() * GetScaleMatrix());
                }

                inline mathematics::linear::Matrix3x3 GetNormalMatrix() const 
                { 
                    return mathematics::linear::Matrix4x4::CreateNormalFrom(GetModelMatrix());;
                }

                inline void SetUniformScale(float scaleFactor)
                {
                    scale.x = scaleFactor;
                    scale.y = scaleFactor;
                    scale.z = scaleFactor;
                }

            private:
                const Mesh& _mesh;
                const materials::Material& _material;

                inline mathematics::linear::Matrix4x4 GetRotationMatrix() const 
                {
                    return mathematics::linear::Matrix4x4::CreateFromRotationPitchYawRoll(
                        mathematics::MathsHelper::DegreesToRadians(rotationDegrees.pitch),
                        mathematics::MathsHelper::DegreesToRadians(rotationDegrees.yaw),
                        mathematics::MathsHelper::DegreesToRadians(rotationDegrees.roll));
                }

                inline mathematics::linear::Matrix4x4 GetTranslationMatrix() const 
                { 
                    return mathematics::linear::Matrix4x4::CreateFromTranslation(position); 
                }

                inline mathematics::linear::Matrix4x4 GetScaleMatrix() const 
                { 
                    return mathematics::linear::Matrix4x4::CreateFromScale(scale); 
                }
            };
        }
    }
}