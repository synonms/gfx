#pragma once

#include <gfx\materials\pbr-material.h>
#include <gfx\primitives\mesh.h>
#include <gfx\transforms\matrix3x3.h>
#include <gfx\transforms\matrix4x4.h>
#include <gfx\geometry\point3.h>
#include <gfx\geometry\vector3.h>

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
                MeshInstance(std::shared_ptr<Mesh> mesh, std::shared_ptr<materials::PBRMaterial> material)
                    : _mesh(mesh)
                    , _material(material)
                {}
                
                geometry::Point3<float> position{ 0.0f, 0.0f, 0.0f };
                geometry::Vector3<float> rotationDegrees{ 0.0f, 0.0f, 0.0f };
                geometry::Vector3<float> scale{ 1.0f, 1.0f, 1.0f };

                inline const materials::PBRMaterial& GetMaterial() const
                {
                    return *_material.get();
                }

                inline const Mesh& GetMesh() const 
                { 
                    return *_mesh.get(); 
                }

                inline transforms::Matrix4x4 GetModelMatrix() const
                { 
                    return GetTranslationMatrix() * (GetRotationMatrix() * GetScaleMatrix());
                }

                inline transforms::Matrix3x3 GetNormalMatrix() const
                { 
                    return transforms::Matrix4x4::CreateNormalFrom(GetModelMatrix());;
                }

                inline void SetUniformScale(float scaleFactor)
                {
                    scale.x = scaleFactor;
                    scale.y = scaleFactor;
                    scale.z = scaleFactor;
                }

            private:
                std::shared_ptr<Mesh> _mesh;
                std::shared_ptr<materials::PBRMaterial> _material;

                inline transforms::Matrix4x4 GetRotationMatrix() const
                {
                    return transforms::Matrix4x4::CreateFromRotationPitchYawRoll(
                        mathematics::MathsHelper::DegreesToRadians(rotationDegrees.pitch),
                        mathematics::MathsHelper::DegreesToRadians(rotationDegrees.yaw),
                        mathematics::MathsHelper::DegreesToRadians(rotationDegrees.roll));
                }

                inline transforms::Matrix4x4 GetTranslationMatrix() const
                { 
                    return transforms::Matrix4x4::CreateFromTranslation(geometry::Point3<float>().VectorTo(position));
                }

                inline transforms::Matrix4x4 GetScaleMatrix() const
                { 
                    return transforms::Matrix4x4::CreateFromScale(scale);
                }
            };
        }
    }
}