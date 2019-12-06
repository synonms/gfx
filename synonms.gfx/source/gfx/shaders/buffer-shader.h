#pragma once

#include <gfx\primitives\mesh.h>

#include <opengl\shader-program.h>

#include <memory>

namespace synonms
{
    namespace gfx
    {
        namespace shaders
        {
            class BufferShader
            {
            public:
                BufferShader(const std::string& vertexShaderSource, const std::string& fragmentShaderSource);

                void Render(int textureSlot, const primitives::Mesh& mesh);


            private:
                std::unique_ptr<api::opengl::ShaderProgram> _shaderProgram{ nullptr };
            };
        }
    }
}