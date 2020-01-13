#pragma once

#include <gfx\geometry\vector2.h>
#include <gfx\geometry\vector3.h>
#include <gfx\primitives\mesh-instance.h>

#include <map>
#include <memory>
#include <string>
#include <vector>

namespace synonms
{
    namespace gfx
    {
        namespace assets
        {
            class ObjModelLoader
            {
            public:
                std::vector<primitives::MeshInstance> Load(const std::string& filePath) const;

            private:
                primitives::Vertex CreateVertex(const std::string& faceIndices, const std::vector<geometry::Vector3<float>>& vertexPositions, const std::vector<geometry::Vector3<float>>& vertexNormals, const std::vector<geometry::Vector2<float>>& textureCoords) const;
                std::map<std::string, std::shared_ptr<materials::PBRMaterial>> LoadMaterialFile(const std::string& directory, const std::string& fileName) const;
            };
        }
    }
}