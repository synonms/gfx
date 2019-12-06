#pragma once

#include <gfx\shaders\phong-shader-uniforms.h>
#include <gfx\primitives\mesh.h>

#include <opengl\shader-program.h>

#include <memory>

namespace synonms
{
    namespace gfx
    {
        namespace shaders
        {
            class PhongShader
            {
            public:
                PhongShader(const std::string& vertexShaderSource, const std::string& fragmentShaderSource);

                void Render(const PhongShaderUniforms& uniforms, const primitives::Mesh& mesh);

            private:
                std::unique_ptr<api::opengl::ShaderProgram> _shaderProgram{ nullptr };
            };
        }
    }
}