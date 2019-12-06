#pragma once

#include <opengl\enumerators\minification-filter-value.h>
#include <opengl\enumerators\magnification-filter-value.h>
#include <opengl\enumerators\target-texture.h>
#include <opengl\enumerators\texture-parameter.h>
#include <opengl\enumerators\texture-wrap-mode.h>
#include <opengl\enumerators\texture-internal-format.h>
#include <opengl\enumerators\texture-format.h>
#include <opengl\enumerators\texture-compare-mode.h>
#include <opengl\enumerators\texture-compare-func.h>
#include <opengl\enumerators\data-type.h>

namespace synonms
{
    namespace gfx
    {
        namespace api
        {
            namespace opengl
            {
                class Texture
                {
                public:
                    Texture(enumerators::TargetTexture targetTexture = enumerators::TargetTexture::Texture2D);
                    Texture(Texture&& other) noexcept;
                    Texture& operator=(Texture&& other) noexcept;
                    ~Texture();

                    Texture(const Texture& other) = delete;
                    Texture& operator=(const Texture& other) = delete;

                public:
                    void Bind() const;
                    inline unsigned int GetTextureId() const { return _textureId; }
                    void SendData(enumerators::TextureInternalFormat internalFormat, int width, int height, enumerators::TextureFormat format, enumerators::DataType dataType, unsigned char* data) const;

                public:
                    static void ActivateSlot(unsigned int slot);
                    static void SetBorderColour(enumerators::TargetTexture targetTexture, const float* rgba);
                    static void SetCompareFunc(enumerators::TargetTexture targetTexture, enumerators::TextureCompareFunc compareFunc);
                    static void SetCompareMode(enumerators::TargetTexture targetTexture, enumerators::TextureCompareMode compareMode);
                    static void SetMinificationFilter(enumerators::TargetTexture targetTexture, enumerators::MinificationFilterValue filterValue);
                    static void SetMagnificationFilter(enumerators::TargetTexture targetTexture, enumerators::MagnificationFilterValue filterValue);
                    static void SetWrapModeS(enumerators::TargetTexture targetTexture, enumerators::TextureWrapMode wrapMode);
                    static void SetWrapModeT(enumerators::TargetTexture targetTexture, enumerators::TextureWrapMode wrapMode);
                    static void Unbind(enumerators::TargetTexture targetTexture);

                private:
                    enumerators::TargetTexture _targetTexture{ enumerators::TargetTexture::Texture2D };
                    unsigned int _textureId{ 0 };
                };
            }
        }
    }
}
