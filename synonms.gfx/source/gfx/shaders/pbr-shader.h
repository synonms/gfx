#pragma once

#include <gfx\materials\pbr-material.h>
#include <gfx\primitives\mesh.h>
#include <gfx\shaders\pbr-shader-data.h>

#include <opengl\shader-program.h>
#include <opengl\texture.h>

#include <memory>
#include <vector>

namespace synonms
{
    namespace gfx
    {
        namespace shaders
        {
            class PBRShader
            {
            public:
                PBRShader(const std::string& vertexShaderSource, const std::string& fragmentShaderSource);

                void Render(const PBRShaderData& data, const primitives::Mesh& mesh);

            private:
                std::unique_ptr<api::opengl::ShaderProgram> _shaderProgram{ nullptr };
                
                unsigned int SetUniforms(api::opengl::Texture* texture, int slot, const std::string& name, const std::vector<std::string>& uniforms) const;
            };
        }
    }
}