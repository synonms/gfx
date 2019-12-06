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

                void Render(const mathematics::linear::Matrix4x4& modelViewProjectionMatrix, const primitives::Mesh& mesh);

            private:
                std::unique_ptr<api::opengl::ShaderProgram> _shaderProgram{ nullptr };
            };
        }
    }
}