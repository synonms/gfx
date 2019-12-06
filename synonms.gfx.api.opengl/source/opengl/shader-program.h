#pragma once

#include <string>

namespace synonms
{
    namespace gfx
    {
        namespace api
        {
            namespace opengl
            {
                class ShaderProgram
                {
                public:
                    ShaderProgram();
                    ShaderProgram(ShaderProgram&& other) noexcept;
                    ShaderProgram& operator=(ShaderProgram&& other) noexcept;
                    virtual ~ShaderProgram();

                    ShaderProgram(const ShaderProgram& other) = delete;
                    ShaderProgram& operator=(const ShaderProgram& other) = delete;

                public:
                    void AttachShader(unsigned int shaderId) const;
                    inline unsigned int GetProgramId() const { return _programId; }
                    int GetUniformLocation(const std::string& uniformName) const;
                    void Link() const;
                    void Use() const;
                    void Validate() const;

                public:
                    static void SetUniformBool(unsigned int location, bool value);
                    static void SetUniformFloat(unsigned int location, float value);
                    static void SetUniformInt(unsigned int location, int value);
                    static void SetUniformVector3(unsigned int location, float value1, float value2, float value3);
                    static void SetUniformVector4(unsigned int location, float value1, float value2, float value3, float value4);
                    static void SetUniformMatrix3x3(unsigned int location, const float* value);
                    static void SetUniformMatrix4x4(unsigned int location, const float* value);

                private:
                    unsigned int _programId{ 0 };
                };
            }
        }
    }
}
