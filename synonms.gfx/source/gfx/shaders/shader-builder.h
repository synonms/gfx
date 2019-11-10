#pragma once

#include <string>
#include <vector>


/*
* Gouraud shading computes colour (including lighting) at vertex level and then simply interpolates in fragment shader
* - This is cheap but leaves lighting artifacts
* Phong shading computes normals at vertex level which are then interpolated in fragment shader and lighting calculated there 
*/

namespace synonms
{
    namespace gfx
    {
        namespace shaders
        {
            enum class GlslType
            {
                Bool,
                Double,
                Float,
                Int,
                Sampler2D,
                Uint,
                Vector2Bool,
                Vector3Bool,
                Vector4Bool,
                Vector2Double,
                Vector3Double,
                Vector4Double,
                Vector2Float,
                Vector3Float,
                Vector4Float,
                Vector2Int,
                Vector3Int,
                Vector4Int,
                Vector2Uint,
                Vector3Uint,
                Vector4Uint
            };

            class GlslTypeMapper
            {
            public:
                static std::string ToString(GlslType type)
                {
                    switch (type)
                    {
                    case GlslType::Bool: return "bool";
                    case GlslType::Double: return "double";
                    case GlslType::Float: return "float";
                    case GlslType::Int: return "int";
                    case GlslType::Sampler2D: return "sampler2D";
                    case GlslType::Uint: return "uint";
                    case GlslType::Vector2Bool: return "bvec2";
                    case GlslType::Vector3Bool: return "bvec3";
                    case GlslType::Vector4Bool: return "bvec4";
                    case GlslType::Vector2Double: return "dvec2";
                    case GlslType::Vector3Double: return "dvec3";
                    case GlslType::Vector4Double: return "dvec4";
                    case GlslType::Vector2Float: return "vec2";
                    case GlslType::Vector3Float: return "vec3";
                    case GlslType::Vector4Float: return "vec4";
                    case GlslType::Vector2Int: return "ivec2";
                    case GlslType::Vector3Int: return "ivec3";
                    case GlslType::Vector4Int: return "ivec4";
                    case GlslType::Vector2Uint: return "uvec2";
                    case GlslType::Vector3Uint: return "uvec3";
                    case GlslType::Vector4Uint: return "uvec4";
                    }

                    return "";
                }
            };

            class ShaderVariable
            {
            public:
                ShaderVariable(GlslType type, const std::string& name) : Type(type), Name(name) {}
                GlslType Type;
                std::string Name;
            };

            class ShaderAttribute
            {
            public:
                ShaderAttribute(int index, GlslType type, const std::string& name) : Index(index), Type(type), Name(name) {}
                int Index;
                GlslType Type;
                std::string Name;
            };

            class ShaderBuilder
            {
            public:
                ShaderBuilder& UseVersion(const std::string& version);
                ShaderBuilder& WithFragmentStatement(const std::string& statement);
                ShaderBuilder& WithVertexStatement(const std::string& statement);
                ShaderBuilder& WithFragmentUniform(GlslType type, const std::string& name);
                ShaderBuilder& WithVertexUniform(GlslType type, const std::string& name);
                ShaderBuilder& WithPassThrough(GlslType type, const std::string& name);
                ShaderBuilder& WithFragmentOutputAtribute(int index, GlslType type, const std::string& name);
                ShaderBuilder& WithVertexInputAtribute(int index, GlslType type, const std::string& name);


                std::string BuildFragmentShader() const;
                std::string BuildVertexShader() const;

            private:
                std::string _version{ "330 core" };
                std::vector<ShaderVariable> _fragmentUniforms{};
                std::vector<ShaderVariable> _vertexUniforms{};
                std::vector<ShaderVariable> _passthroughs{};
                std::vector<ShaderAttribute> _vertexInputAttributes{};
                std::vector<ShaderAttribute> _fragmentOutputAttributes{};
                std::vector<std::string> _fragmentStatements{};
                std::vector<std::string> _vertexStatements{};

                void WriteVersion(std::stringstream& stream) const;
                void WriteFragmentOutputAttributes(std::stringstream& stream) const;
                void WriteVertexInputAttributes(std::stringstream& stream) const;
                void WriteFragmentUniforms(std::stringstream& stream) const;
                void WriteFragmentBody(std::stringstream& stream) const;
                void WriteVertexBody(std::stringstream& stream) const;
                void WriteVertexUniforms(std::stringstream& stream) const;
                void WriteFragmentPassthroughs(std::stringstream& stream) const;
                void WriteVertexPassthroughs(std::stringstream& stream) const;
            };
        }
    }
}