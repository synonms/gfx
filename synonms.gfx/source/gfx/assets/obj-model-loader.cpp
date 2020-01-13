#include "obj-model-loader.h"

#include <gfx\io\image.h>
#include <gfx\materials\pbr-material.h>
#include <gfx\materials\texture-factory.h>
#include <gfx\primitives\vertex.h>
#include <gfx\utilities\string-extensions.h>

#include <exception>
#include <fstream>
#include <map>
#include <sstream>

using namespace synonms::gfx::assets;
using namespace synonms::gfx::geometry;
using namespace synonms::gfx::io;
using namespace synonms::gfx::materials;
using namespace synonms::gfx::primitives;
using namespace synonms::gfx::utilities;

std::vector<MeshInstance> ObjModelLoader::Load(const std::string& filePath) const
{
    std::ifstream fileStream;
    fileStream.open(filePath.c_str(), std::ios::in);

    if (fileStream.fail()) {
        auto message = "Cannot open file '" + filePath + "'";
        throw std::exception(message.c_str());
    }

    auto directory = filePath.substr(0, filePath.find_last_of('/'));

    std::vector<Vector3<float>> vertexPositions;
    std::vector<Vector3<float>> vertexNormals;
    std::vector<Vector2<float>> textureCoords;

    std::vector<std::string> groups;
    std::map<std::string, std::vector<Vertex>> vertices;
    std::map<std::string, std::vector<unsigned int>> indices;
    std::map<std::string, std::shared_ptr<PBRMaterial>> materials;
    std::map<std::string, std::string> groupToMaterialMapper;

    std::string currentGroup;
    std::string lineBuffer;

    while (std::getline(fileStream, lineBuffer))
    {
        StringExtensions::Trim(lineBuffer);

        if (lineBuffer.empty()) continue;
        if (lineBuffer[0] == '\0') continue;   // empty line
        if (lineBuffer[0] == '#') continue;    // comment line
        if (lineBuffer.length() < 2) continue; // Insufficient data

        const auto& tokens = StringExtensions::Tokenise(lineBuffer, ' ');

        if (tokens.size() <= 1) continue;  // Insufficient tokens to process

        if (tokens[0] == "v")
        {
            Vector3<float> position;
            position.x = tokens.size() > 1 ? std::stof(tokens[1]) : 0.0f;
            position.y = tokens.size() > 2 ? std::stof(tokens[2]) : 0.0f;
            position.z = tokens.size() > 3 ? std::stof(tokens[3]) : 0.0f;
            vertexPositions.push_back(position);
            continue;
        }

        if (tokens[0] == "vn")
        {
            Vector3<float> normal;
            normal.x = tokens.size() > 1 ? std::stof(tokens[1]) : 0.0f;
            normal.y = tokens.size() > 2 ? std::stof(tokens[2]) : 0.0f;
            normal.z = tokens.size() > 3 ? std::stof(tokens[3]) : 0.0f;
            vertexNormals.push_back(normal);
            continue;
        }

        if (tokens[0] == "vt") 
        {
            Vector2<float> textureCoord;
            textureCoord.u = tokens.size() > 1 ? std::stof(tokens[1]) : 0.0f;
            textureCoord.v = tokens.size() > 2 ? std::stof(tokens[2]) : 0.0f;
            textureCoords.push_back(textureCoord);
            continue;
        }

        // line
        if (tokens[0] == "l") 
        {
            // TODO
            continue;
        }

        // points
        if (tokens[0] == "p") 
        {
            // TODO
            continue;
        }

        // face
        if (tokens[0] == "f") 
        {
            if (tokens.size() < 4) continue;  // Insufficient data

            auto vertex1 = CreateVertex(tokens[1], vertexPositions, vertexNormals, textureCoords);

            if (std::find(std::begin(groups), std::end(groups), currentGroup) == std::end(groups))
            {
                groups.push_back(currentGroup);
            }

            vertices[currentGroup].push_back(vertex1);
            auto vertex1Index = vertices[currentGroup].size() - 1;

            for (size_t i = 3; i < tokens.size(); ++i)
            {
                auto vertex2 = CreateVertex(tokens[i-1ull], vertexPositions, vertexNormals, textureCoords);
                auto vertex3 = CreateVertex(tokens[i], vertexPositions, vertexNormals, textureCoords);

                indices[currentGroup].push_back(vertex1Index);

                // TODO - Optimise this to avoid adding same vertex multi times

                vertices[currentGroup].push_back(vertex2);
                indices[currentGroup].push_back(vertices[currentGroup].size() - 1);

                vertices[currentGroup].push_back(vertex3);
                indices[currentGroup].push_back(vertices[currentGroup].size() - 1);
            }

            continue;
        }

        // use mtl
        if (tokens[0] == "usemtl") 
        {
            if (tokens.size() < 2) continue;  // Insufficient data

            const auto& materialName = tokens[1];

            groupToMaterialMapper[currentGroup] = materialName;

            continue;
        }

        // load mtl
        if (tokens[0] == "mtllib") 
        {
            if (tokens.size() < 2) continue;  // Insufficient data

            const auto& materialFileName = tokens[1];

            materials = LoadMaterialFile(directory, materialFileName);

            continue;
        }

        // group name
        if (tokens[0] == "g") 
        {
            if (tokens.size() < 2) continue;  // Insufficient data

            currentGroup = tokens[1];

            continue;
        }

        // object name
        if (tokens[0] == "o") 
        {
            // TODO
            continue;
        }

        // Tags
        if (tokens[0] == "t") 
        {
            // TODO
            continue;
        }

        // Smoothing groups
        if (tokens[0] == "s") 
        {
            // TODO
            continue;
        }

        // Ignore unknown command.
    }

    std::vector<MeshInstance> meshInstances;

    for (const auto& group : groups)
    {
        auto newMesh = std::make_shared<Mesh>(vertices[group], indices[group]);
        auto newMaterial = materials[groupToMaterialMapper[group]];
        meshInstances.push_back(MeshInstance(newMesh, newMaterial));
    }

    return meshInstances;
}

Vertex ObjModelLoader::CreateVertex(const std::string& faceIndices, const std::vector<Vector3<float>>& vertexPositions, const std::vector<Vector3<float>>& vertexNormals, const std::vector<Vector2<float>>& textureCoords) const
{
    auto indices = StringExtensions::Tokenise(faceIndices, '/');

    auto positionIndex = std::stoull(indices[0]);
    auto texCoordIndex = indices.size() > 1 && indices[1].length() > 0 ? std::stoull(indices[1]) : 0;
    auto normalIndex = indices.size() > 2 && indices[2].length() > 0 ? std::stoull(indices[2]) : 0;

    auto position = vertexPositions[positionIndex - 1ull];
    auto normal = normalIndex > 0 ? vertexNormals[normalIndex - 1ull] : Vector3<float>(0.0f, 0.0f, 1.0f);
    auto texCoord = texCoordIndex > 0 ? textureCoords[texCoordIndex - 1ull] : Vector2<float>(0.0f, 0.0f);
    // TODO - Calculate tangent
    auto tangent = Vector3<float>(0.0f, 1.0f, 0.0f);

    return Vertex(position, normal, texCoord, tangent);
}

std::map<std::string, std::shared_ptr<PBRMaterial>> ObjModelLoader::LoadMaterialFile(const std::string& directory, const std::string& fileName) const
{
    std::ifstream fileStream;
    auto filePath = directory + "/" + fileName;
    fileStream.open(filePath.c_str(), std::ios::in);

    if (fileStream.fail()) {
        auto message = "Cannot open file '" + filePath + "'";
        throw std::exception(message.c_str());
    }

    std::string currentMaterialName;
    std::string lineBuffer;
    std::shared_ptr<PBRMaterial> currentMaterial = nullptr;

    std::map<std::string, std::shared_ptr<PBRMaterial>> materials;

    while (std::getline(fileStream, lineBuffer))
    {
        StringExtensions::Trim(lineBuffer);

        if (lineBuffer.empty()) continue;
        if (lineBuffer[0] == '\0') continue;   // empty line
        if (lineBuffer[0] == '#') continue;    // comment line
        if (lineBuffer.length() < 2) continue; // Insufficient data

        const auto& tokens = StringExtensions::Tokenise(lineBuffer, ' ');

        if (tokens.size() <= 1) continue;  // Insufficient tokens to process

        if (tokens[0] == "newmtl")
        {
            if (tokens.size() < 2) continue;  // Insufficient data

            if (!currentMaterialName.empty() && currentMaterial != nullptr)
            {
                materials[currentMaterialName] = currentMaterial;
            }

            currentMaterialName = tokens[1];
            currentMaterial = std::make_shared<PBRMaterial>();

            continue;
        }

        if (tokens[0] == "map_Ka")
        {
            if (tokens.size() < 2) continue;  // Insufficient data

            const auto& imagePath = tokens[1];

            Image image(directory + "/" + imagePath);

            currentMaterial->AmbientOcclusion = TextureFactory::CreateColour(image);
        }

        if (tokens[0] == "map_Kd")
        {
            if (tokens.size() < 2) continue;  // Insufficient data

            const auto& imagePath = tokens[1];

            Image image(directory + "/" + imagePath);

            currentMaterial->Albedo = TextureFactory::CreateColour(image);
        }

        if (tokens[0] == "Pm/map_Pm")
        {
            if (tokens.size() < 2) continue;  // Insufficient data

            const auto& imagePath = tokens[1];

            Image image(directory + "/" + imagePath);

            currentMaterial->Metallic = TextureFactory::CreateColour(image);
        }

        if (tokens[0] == "norm")
        {
            if (tokens.size() < 2) continue;  // Insufficient data

            const auto& imagePath = tokens[1];

            Image image(directory + "/" + imagePath);

            currentMaterial->Normal = TextureFactory::CreateColour(image);
        }

        if (tokens[0] == "Pr/map_Pr")
        {
            if (tokens.size() < 2) continue;  // Insufficient data

            const auto& imagePath = tokens[1];

            Image image(directory + "/" + imagePath);

            currentMaterial->Roughness = TextureFactory::CreateColour(image);
        }
    }

    if (!currentMaterialName.empty() && currentMaterial != nullptr)
    {
        materials[currentMaterialName] = currentMaterial;
    }

    return materials;
}