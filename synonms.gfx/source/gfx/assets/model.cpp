#include "model.h"

#include <gfx\primitives\vertex.h>
#include <gfx\io\image.h>
#include <gfx\materials\texture-factory.h>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include <exception>

using namespace synonms::gfx::assets;
using namespace synonms::gfx::geometry;
using namespace synonms::gfx::io;
using namespace synonms::gfx::materials;
using namespace synonms::gfx::primitives;
using namespace synonms::gfx::api::opengl;

class Model::Implementation
{
public:
    Implementation(const std::string& filePath)
    {
        Assimp::Importer importer;
        const auto scene = importer.ReadFile(filePath.c_str(), aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_GenNormals);

        if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
        {
            auto message = "ERROR - ASSIMP: " + std::string(importer.GetErrorString());
            throw std::exception(message.c_str());
        }

        directory = filePath.substr(0, filePath.find_last_of('/'));

        ProcessNode(scene->mRootNode, scene);
    }

    std::string directory;
    std::vector<std::unique_ptr<MeshInstance>> meshes;

    void ProcessNode(aiNode* node, const aiScene* scene)
    {
        // process all the node's meshes (if any)
        for (unsigned int i = 0; i < node->mNumMeshes; i++)
        {
            aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
            meshes.push_back(ProcessMesh(mesh, scene));
        }
        // then do the same for each of its children
        for (unsigned int i = 0; i < node->mNumChildren; i++)
        {
            ProcessNode(node->mChildren[i], scene);
        }
    }

    std::unique_ptr<MeshInstance> ProcessMesh(aiMesh* assimpMesh, const aiScene* assimpScene)
    {
        std::vector<Vertex> vertices;
        std::vector<unsigned int> indices;

        for (auto i = 0u; i < assimpMesh->mNumVertices; i++)
        {
            vertices.push_back(
                Vertex(
                    Vector3<float>(assimpMesh->mVertices[i].x, assimpMesh->mVertices[i].y, assimpMesh->mVertices[i].z),
                    Vector3<float>(assimpMesh->mNormals[i].x, assimpMesh->mNormals[i].y, assimpMesh->mNormals[i].z),
                    assimpMesh->HasTextureCoords(0) ? Vector2<float>(assimpMesh->mTextureCoords[0][i].x, assimpMesh->mTextureCoords[0][i].y) : Vector2<float>(),
                    assimpMesh->HasTangentsAndBitangents() ? Vector3<float>(assimpMesh->mTangents[i].x, assimpMesh->mTangents[i].y, assimpMesh->mTangents[i].z) : Vector3<float>()
                )
            );
        }

        for (unsigned int i = 0; i < assimpMesh->mNumFaces; i++)
        {
            auto face = assimpMesh->mFaces[i];
            for (auto j = 0u; j < face.mNumIndices; j++)
            {
                indices.push_back(face.mIndices[j]);
            }
        }

        auto mesh = std::make_shared<Mesh>(vertices, indices);
        auto pbrMaterial = std::make_shared<PBRMaterial>();

        if (assimpMesh->mMaterialIndex >= 0)
        {
            aiMaterial* material = assimpScene->mMaterials[assimpMesh->mMaterialIndex];
            pbrMaterial->Albedo = LoadMaterialTexture(material, aiTextureType::aiTextureType_DIFFUSE);
            pbrMaterial->Normal = LoadMaterialTexture(material, aiTextureType::aiTextureType_NORMALS);
            pbrMaterial->Roughness = LoadMaterialTexture(material, aiTextureType::aiTextureType_DIFFUSE_ROUGHNESS);
            pbrMaterial->Metallic = LoadMaterialTexture(material, aiTextureType::aiTextureType_METALNESS);
            pbrMaterial->AmbientOcclusion = LoadMaterialTexture(material, aiTextureType::aiTextureType_AMBIENT_OCCLUSION);
        }

        return std::make_unique<MeshInstance>(mesh, pbrMaterial);
    }

    std::shared_ptr<Texture> LoadMaterialTexture(aiMaterial* material, aiTextureType type)
    {
        if (material->GetTextureCount(type) <= 0) return nullptr;

        aiString str;
        material->GetTexture(type, 0, &str);

        Image image(directory + '/' + str.C_Str());
        return TextureFactory::CreateColour(image);
    }
};


Model::Model(const std::string& filePath)
{
    _implementation = std::make_unique<Implementation>(filePath);
}

Model::~Model()
{
}

const std::vector<std::unique_ptr<MeshInstance>>& Model::GetMeshInstances() const
{
    return _implementation->meshes;
}
