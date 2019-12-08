#pragma once

#include <gfx\mathematics\linear\matrix4x4.h>
#include <gfx\primitives\mesh.h>

#include <opengl\shader-program.h>

#include <memory>

namespace synonms
{
    namespace gfx
    {
        namespace shaders
        {
            class ShadowmapShader
            {
            public:
                ShadowmapShader(const std::string& vertexShaderSource, const std::string& fragmentShaderSource);

                void RenderOrthographic(const mathematics::linear::Matrix4x4& viewProjectionMatrix, const mathematics::linear::Matrix4x4& modelMatrix, const primitives::Mesh& mesh);
                void RenderPerspective(const mathematics::linear::Matrix4x4& viewProjectionMatrix, const mathematics::linear::Matrix4x4& modelMatrix, float nearPlane, float farPlane, const primitives::Mesh& mesh);

            private:
                std::unique_ptr<api::opengl::ShaderProgram> _shaderProgram{ nullptr };
            };
        }
    }
}