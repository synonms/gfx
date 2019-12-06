#pragma once

#include <opengl\enumerators\data-type.h>
#include <opengl\enumerators\data-usage.h>
#include <opengl\enumerators\draw-mode.h>

namespace synonms
{
    namespace gfx
    {
        namespace api
        {
            namespace opengl
            {
                class IndexBuffer
                {
                public:
                    IndexBuffer();
                    IndexBuffer(IndexBuffer&& other) noexcept;
                    IndexBuffer& operator=(IndexBuffer&& other) noexcept;
                    ~IndexBuffer();

                    IndexBuffer(const IndexBuffer& other) = delete;
                    IndexBuffer& operator=(const IndexBuffer& other) = delete;

                public:
                    void Bind() const;
                    inline unsigned int GetIndexBufferId() const { return _indexBufferId; }

                public:
                    static void Draw(enumerators::DrawMode drawMode, int noOfIndices, enumerators::DataType dataType);
                    static void SendData(const void* data, size_t noOfBytes, enumerators::DataUsage dataUsage);

                private:
                    unsigned int _indexBufferId{ 0 };
                };
            }
        }
    }
}
