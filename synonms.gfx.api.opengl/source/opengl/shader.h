#pragma once

#include <string>

#include <opengl\enumerators\shader-type.h>

namespace synonms
{
    namespace gfx
    {
        namespace api
        {
            namespace opengl
            {
                class Shader
                {
                public:
                    Shader(enumerators::ShaderType shaderType);
                    Shader(Shader&& other) noexcept;
                    Shader& operator=(Shader&& other) noexcept;
                    ~Shader();

                    Shader() = delete;
                    Shader(const Shader& other) = delete;
                    Shader& operator=(const Shader& other) = delete;

                public:
                    bool Compile() const;
                    std::string GetLog() const;
                    inline unsigned int GetShaderId() const { return _shaderId; }
                    void SetSource(const std::string& sourceCode) const;

                private:
                    unsigned int _shaderId{ 0 };
                };
            }
        }
    }
}
