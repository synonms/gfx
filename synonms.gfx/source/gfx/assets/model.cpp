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
    std::vector<std::unique_ptr<Mesh>> meshes;
    std::vector<std::shared_ptr<Texture>> textures;

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

    std::unique_ptr<Mesh> ProcessMesh(aiMesh* mesh, const aiScene* scene)
    {
        std::vector<Vertex> vertices;
        std::vector<unsigned int> indices;

        for (auto i = 0u; i < mesh->mNumVertices; i++)
        {
            vertices.push_back(
                Vertex(
                    Vector3<float>(mesh->mVertices[i].x, mesh->mVertices[i].y, mesh->mVertices[i].z),
                    Vector3<float>(mesh->mNormals[i].x, mesh->mNormals[i].y, mesh->mNormals[i].z),
                    mesh->HasTextureCoords(0) ? Vector2<float>(mesh->mTextureCoords[0][i].x, mesh->mTextureCoords[0][i].y) : Vector2<float>(),
                    mesh->HasTangentsAndBitangents() ? Vector3<float>(mesh->mTangents[i].x, mesh->mTangents[i].y, mesh->mTangents[i].z) : Vector3<float>()
                )
            );
        }

        for (unsigned int i = 0; i < mesh->mNumFaces; i++)
        {
            auto face = mesh->mFaces[i];
            for (auto j = 0u; j < face.mNumIndices; j++)
            {
                indices.push_back(face.mIndices[j]);
            }
        }

        if (mesh->mMaterialIndex >= 0)
        {
            aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];
            LoadMaterialTextures(material, aiTextureType_DIFFUSE, "texture_diffuse");
            LoadMaterialTextures(material, aiTextureType_SPECULAR, "texture_specular");
        }

        return std::make_unique<Mesh>(vertices, indices);
    }

    void LoadMaterialTextures(aiMaterial* material, aiTextureType type, const std::string& typeName)
    {
        // TODO - stick these in a shared map somewhere and link them via a MeshInstance

        for (auto i = 0u; i < material->GetTextureCount(type); i++)
        {
            aiString str;
            material->GetTexture(type, i, &str);

            Image image(str.C_Str());
            textures.push_back(TextureFactory::CreateColour(image));
        }
    }
};


Model::Model(const std::string& filePath)
{
    _implementation = std::make_unique<Implementation>(filePath);
}
