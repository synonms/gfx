#pragma once

#include <gfx\primitives\mesh.h>
#include <gfx\mathematics\linear\matrix3x3.h>
#include <gfx\mathematics\linear\matrix4x4.h>

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

                void Render(const mathematics::linear::Matrix4x4& projectionMatrix, const mathematics::linear::Matrix4x4& viewMatrix, const mathematics::linear::Matrix4x4& modelMatrix, const mathematics::linear::Matrix3x3& normalMatrix, const primitives::Mesh& mesh);

            private:
                std::unique_ptr<api::opengl::ShaderProgram> _shaderProgram{ nullptr };
            };
        }
    }
}