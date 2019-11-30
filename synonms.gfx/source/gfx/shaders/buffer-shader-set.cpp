#include "buffer-shader-set.h"

using namespace synonms::gfx::primitives;
using namespace synonms::gfx::shaders;

BufferShaderSet::BufferShaderSet(const std::string& vertexShaderSource, const std::string& fragmentShaderSource)
    : ShaderSet(vertexShaderSource, fragmentShaderSource)
{}

void BufferShaderSet::Render(int bufferTextureId, const Mesh& mesh)
{
    Use();

    SetUniform("fu_bufferTextureSlot", bufferTextureId);

    mesh.Draw();
}
