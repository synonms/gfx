#pragma once

#include <gfx\primitives\mesh.h>
#include <gfx\materials\material.h>
#include <gfx\mathematics\linear\matrix3x3.h>
#include <gfx\mathematics\linear\matrix4x4.h>
#include <gfx\mathematics\linear\transform.h>

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
                
                inline const materials::Material& GetMaterial() const { return _material; }
                inline const Mesh& GetMesh() const { return _mesh; }
                inline float* GetPositionData() { return &_transform.position.x; }
                inline float* GetRotationData() { return &_transform.rotationDegrees.x; }
                inline float* GetScaleData() { return &_transform.scale.x; }
                inline mathematics::linear::Matrix4x4 GetModelMatrix() const { return _transform.GetModelMatrix(); }
                inline mathematics::linear::Matrix3x3 GetNormalMatrix() const { return _transform.GetNormalMatrix(); }
                inline void SetPosition(const mathematics::linear::Vector3<float>& position) { _transform.position = position; }
                inline void SetRotation(const mathematics::linear::Vector3<float>& rotationDegrees) { _transform.rotationDegrees = rotationDegrees; }
                inline void SetScale(const mathematics::linear::Vector3<float>& scale) { _transform.scale = scale; }

            private:
                const Mesh& _mesh;
                const materials::Material& _material;

                mathematics::linear::Transform _transform{};
            };
        }
    }
}