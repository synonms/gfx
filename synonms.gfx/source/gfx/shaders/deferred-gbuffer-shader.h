#pragma once

#include <gfx\shaders\deferred-gbuffer-shader-uniforms.h>
#include <gfx\primitives\mesh.h>

#include <opengl\shader-program.h>

#include <memory>

namespace synonms
{
    namespace gfx
    {
        namespace shaders
        {
            class DeferredGBufferShader
            {
            public:
                DeferredGBufferShader(const std::string& vertexShaderSource, const std::string& fragmentShaderSource);

                void Render(const DeferredGBufferShaderUniforms& data, const primitives::Mesh& mesh);

            private:
                std::unique_ptr<api::opengl::ShaderProgram> _shaderProgram{ nullptr };

                unsigned int SetUniforms(api::opengl::Texture* texture, int slot, const std::string& name, const std::vector<std::string>& uniforms) const;
            };
        }
    }
}