#pragma once

#include <gfx\transforms\matrix4x4.h>
#include <gfx\primitives\mesh.h>

#include <opengl\shader-program.h>
#include <opengl\texture.h>

#include <memory>

namespace synonms
{
    namespace gfx
    {
        namespace shaders
        {
            class SkyBoxShader
            {
            public:
                SkyBoxShader(const std::string& vertexShaderSource, const std::string& fragmentShaderSource);

                void Render(const transforms::Matrix4x4& sceneRotationMatrix, const transforms::Matrix4x4& projectionMatrix, const api::opengl::Texture& skyBoxTexture, const primitives::Mesh& mesh);

            private:
                std::unique_ptr<api::opengl::ShaderProgram> _shaderProgram{ nullptr };
            };
        }
    }
}