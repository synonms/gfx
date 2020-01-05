#pragma once

#include <gfx\shaders\deferred-lighting-shader-uniforms.h>
#include <gfx\primitives\mesh.h>

#include <opengl\shader-program.h>

#include <memory>

namespace synonms
{
    namespace gfx
    {
        namespace shaders
        {
            class DeferredLightingShader
            {
            public:
                DeferredLightingShader(const std::string& vertexShaderSource, const std::string& fragmentShaderSource);

                void Render(const DeferredLightingShaderUniforms& data, const primitives::Mesh& mesh);

            private:
                std::unique_ptr<api::opengl::ShaderProgram> _shaderProgram{ nullptr };
            };
        }
    }
}