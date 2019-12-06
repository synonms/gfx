#pragma once

#include <opengl\enumerators\data-usage.h>

namespace synonms
{
    namespace gfx
    {
        namespace api
        {
            namespace opengl
            {
                class VertexBuffer
                {
                public:
                    VertexBuffer();
                    VertexBuffer(VertexBuffer&& other) noexcept;
                    VertexBuffer& operator=(VertexBuffer&& other) noexcept;
                    ~VertexBuffer();

                    VertexBuffer(const VertexBuffer& other) = delete;
                    VertexBuffer& operator=(const VertexBuffer& other) = delete;

                public:
                    void Bind() const;
                    inline unsigned int GetVertexBufferId() const { return _vertexBufferId; }

                public:
                    static void SendData(const void* data, size_t noOfBytes, enumerators::DataUsage dataUsage);

                private:
                    unsigned int _vertexBufferId{ 0 };
                };
            }
        }
    }
}
