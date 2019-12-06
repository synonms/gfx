#include "buffer-shader.h"

#include <gfx\shaders\shader-extensions.h>

#include <opengl\factories\shader-factory.h>

using namespace synonms::gfx::primitives;
using namespace synonms::gfx::shaders;
using namespace synonms::gfx::api;

BufferShader::BufferShader(const std::string& vertexShaderSource, const std::string& fragmentShaderSource)
{
    _shaderProgram = opengl::factories::ShaderFactory::Create(vertexShaderSource, fragmentShaderSource);
}

void BufferShader::Render(int textureSlot, const Mesh& mesh)
{
    _shaderProgram->Use();

    ShaderExtensions::SetUniform(*_shaderProgram.get(), "fu_bufferTextureSlot", textureSlot);

    mesh.Draw();
}
