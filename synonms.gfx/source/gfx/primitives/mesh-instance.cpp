#include "mesh-instance.h"

using namespace synonms::gfx::mathematics::linear;
using namespace synonms::gfx::primitives;

MeshInstance::MeshInstance(const Mesh& mesh)
    : _mesh(mesh)
{
}

Transform& MeshInstance::GetTransform()
{
    return _transform;
}