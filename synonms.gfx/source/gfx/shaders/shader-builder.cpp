#include "shader-builder.h"

#include <sstream>

using namespace synonms::gfx::shaders;

ShaderBuilder& ShaderBuilder::UseVersion(const std::string& version)
{
    _version = version;

    return *this;
}

ShaderBuilder& ShaderBuilder::WithFragmentStatement(const std::string& statement)
{
    _fragmentStatements.push_back(statement);

    return *this;
}

ShaderBuilder& ShaderBuilder::WithVertexStatement(const std::string& statement)
{
    _vertexStatements.push_back(statement);

    return *this;
}

ShaderBuilder& ShaderBuilder::WithPassThrough(GlslType type, const std::string& name)
{
    _passthroughs.push_back(ShaderVariable(type, name));

    return *this;
}

ShaderBuilder& ShaderBuilder::WithFragmentUniform(GlslType type, const std::string& name)
{
    _fragmentUniforms.push_back(ShaderVariable(type, name));

    return *this;
}

ShaderBuilder& ShaderBuilder::WithVertexUniform(GlslType type, const std::string& name)
{
    _vertexUniforms.push_back(ShaderVariable(type, name));

    return *this;
}

ShaderBuilder& ShaderBuilder::WithFragmentOutputAtribute(int index, GlslType type, const std::string& name)
{
    _fragmentOutputAttributes.push_back(ShaderAttribute(index, type, name));

    return *this;
}

ShaderBuilder& ShaderBuilder::WithVertexInputAtribute(int index, GlslType type, const std::string& name)
{
    _vertexInputAttributes.push_back(ShaderAttribute(index, type, name));

    return *this;
}

std::string ShaderBuilder::BuildFragmentShader() const
{
    std::stringstream stream;

    WriteVersion(stream);
    WriteFragmentPassthroughs(stream);
    WriteFragmentUniforms(stream);
    WriteFragmentOutputAttributes(stream);
    WriteFragmentBody(stream);

    return stream.str();
}

std::string ShaderBuilder::BuildVertexShader() const
{
    std::stringstream stream;

    WriteVersion(stream);
    WriteVertexInputAttributes(stream);
    WriteVertexUniforms(stream);
    WriteVertexPassthroughs(stream);
    WriteVertexBody(stream);

    return stream.str();
}

void ShaderBuilder::WriteVersion(std::stringstream& stream) const
{
    stream << "#version " << _version << std::endl;
    stream << std::endl;
}

void ShaderBuilder::WriteFragmentOutputAttributes(std::stringstream& stream) const
{
    for (const auto& attribute : _fragmentOutputAttributes)
    {
        stream << "layout(location = " << attribute.Index << ") out " << GlslTypeMapper::ToString(attribute.Type) << " " << attribute.Name << ";" << std::endl;
    }
    stream << std::endl;
}

void ShaderBuilder::WriteVertexInputAttributes(std::stringstream& stream) const
{
    for (const auto& attribute : _vertexInputAttributes)
    {
        stream << "layout(location = " << attribute.Index << ") in " << GlslTypeMapper::ToString(attribute.Type) << " " << attribute.Name << ";" << std::endl;
    }
    stream << std::endl;
}

void ShaderBuilder::WriteFragmentUniforms(std::stringstream& stream) const
{
    for (const auto& uniform : _fragmentUniforms)
    {
        stream << "uniform " << GlslTypeMapper::ToString(uniform.Type) << " " << uniform.Name << ";" << std::endl;
    }
    stream << std::endl;
}

void ShaderBuilder::WriteFragmentBody(std::stringstream& stream) const
{
    stream << "void main()" << std::endl;
    stream << "{" << std::endl;

    for (const auto& statement : _fragmentStatements)
    {
        stream << statement << ";" << std::endl;
    }

    stream << "}" << std::endl;
}

void ShaderBuilder::WriteVertexBody(std::stringstream& stream) const
{
    stream << "void main()" << std::endl;
    stream << "{" << std::endl;

    for (const auto& statement : _vertexStatements)
    {
        stream << statement << ";" << std::endl;
    }

    stream << "}" << std::endl;
}

void ShaderBuilder::WriteVertexUniforms(std::stringstream& stream) const
{
    for (const auto& uniform : _vertexUniforms)
    {
        stream << "uniform " << GlslTypeMapper::ToString(uniform.Type) << " " << uniform.Name << ";" << std::endl;
    }
    stream << std::endl;
}

void ShaderBuilder::WriteFragmentPassthroughs(std::stringstream& stream) const
{
    for (const auto& passthrough : _passthroughs)
    {
        stream << "in " << GlslTypeMapper::ToString(passthrough.Type) << " " << passthrough.Name << ";" << std::endl;
    }
    stream << std::endl;
}

void ShaderBuilder::WriteVertexPassthroughs(std::stringstream& stream) const
{
    for (const auto& passthrough : _passthroughs)
    {
        stream << "out " << GlslTypeMapper::ToString(passthrough.Type) << " " << passthrough.Name << ";" << std::endl;
    }
    stream << std::endl;
}