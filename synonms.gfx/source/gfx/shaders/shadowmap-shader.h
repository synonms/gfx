#pragma once

#include <gfx\transforms\matrix4x4.h>
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

                void RenderOrthographic(const transforms::Matrix4x4& viewProjectionMatrix, const transforms::Matrix4x4& modelMatrix, const primitives::Mesh& mesh);
                void RenderPerspective(const transforms::Matrix4x4& viewProjectionMatrix, const transforms::Matrix4x4& modelMatrix, float nearPlane, float farPlane, const primitives::Mesh& mesh);

            private:
                std::unique_ptr<api::opengl::ShaderProgram> _shaderProgram{ nullptr };
            };
        }
    }
}