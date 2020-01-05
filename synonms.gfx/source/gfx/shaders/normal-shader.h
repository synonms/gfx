#pragma once

#include <gfx\primitives\mesh.h>
#include <gfx\transforms\matrix3x3.h>
#include <gfx\transforms\matrix4x4.h>

#include <opengl\shader-program.h>

#include <memory>

namespace synonms
{
    namespace gfx
    {
        namespace shaders
        {
            class NormalShader
            {
            public:
                NormalShader(const std::string& vertexShaderSource, const std::string& fragmentShaderSource, const std::string& geometryShaderSource);

                void Render(const transforms::Matrix4x4& projectionMatrix, const transforms::Matrix4x4& viewMatrix, const transforms::Matrix4x4& modelMatrix, const transforms::Matrix3x3& normalMatrix, const primitives::Mesh& mesh);

            private:
                std::unique_ptr<api::opengl::ShaderProgram> _shaderProgram{ nullptr };
            };
        }
    }
}