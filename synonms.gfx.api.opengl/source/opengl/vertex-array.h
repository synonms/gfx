#pragma once

namespace synonms
{
    namespace gfx
    {
        namespace api
        {
            namespace opengl
            {
                class VertexArray
                {
                public:
                    VertexArray();
                    VertexArray(VertexArray&& other) noexcept;
                    VertexArray& operator=(VertexArray&& other) noexcept;
                    ~VertexArray();

                    VertexArray(const VertexArray& other) = delete;
                    VertexArray& operator=(const VertexArray& other) = delete;

                public:
                    void Bind() const;
                    inline unsigned int GetVertexArrayId() const { return _vertexArrayId; }

                private:
                    unsigned int _vertexArrayId{ 0 };
                };
            }
        }
    }
}
