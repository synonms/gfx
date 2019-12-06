#pragma once

#include <opengl\shader-program.h>

#include <memory>

namespace synonms
{
    namespace gfx
    {
        namespace api
        {
            namespace opengl
            {
                namespace factories
                {
                    class ShaderFactory
                    {
                    public:
                        static std::unique_ptr<ShaderProgram> Create(const std::string& vertexShaderSource, const std::string& fragmentShaderSource);
                    };
                }
            }
        }
    }
}
