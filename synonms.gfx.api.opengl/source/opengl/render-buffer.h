#pragma once

#include <opengl\enumerators\texture-internal-format.h>

namespace synonms
{
    namespace gfx
    {
        namespace api
        {
            namespace opengl
            {
                class RenderBuffer
                {
                public:
                    RenderBuffer();
                    RenderBuffer(RenderBuffer&& other) noexcept;
                    RenderBuffer& operator=(RenderBuffer&& other) noexcept;
                    ~RenderBuffer();

                    RenderBuffer(const RenderBuffer& other) = delete;
                    RenderBuffer& operator=(const RenderBuffer& other) = delete;

                public:
                    void Allocate(enumerators::TextureInternalFormat internalFormat, int width, int height) const;
                    void Bind() const;
                    inline unsigned int GetRenderBufferId() const { return _renderBufferId; }

                private:
                    unsigned int _renderBufferId{ 0 };
                };
            }
        }
    }
}
