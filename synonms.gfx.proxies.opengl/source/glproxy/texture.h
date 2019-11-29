#pragma once

#include <glproxy\enumerators\minification-filter-value.h>
#include <glproxy\enumerators\magnification-filter-value.h>
#include <glproxy\enumerators\target-texture.h>
#include <glproxy\enumerators\texture-parameter.h>
#include <glproxy\enumerators\texture-wrap-mode.h>
#include <glproxy\enumerators\texture-internal-format.h>
#include <glproxy\enumerators\texture-format.h>
#include <glproxy\enumerators\texture-compare-mode.h>
#include <glproxy\enumerators\texture-compare-func.h>
#include <glproxy\enumerators\data-type.h>

struct GLFWwindow;

namespace synonms
{
    namespace gfx
    {
        namespace proxies
        {
            namespace opengl
            {
                class Texture
                {
                public:
                    static void ActivateSlot(unsigned int slot, bool throwOnError = false);
                    static void Bind(enumerators::TargetTexture targetTexture, unsigned int textureId, bool throwOnError = false);
                    static void Delete(unsigned int textureId, bool throwOnError = false);
                    static unsigned int Generate(bool throwOnError = false);
                    static void SendData(enumerators::TargetTexture targetTexture, enumerators::TextureInternalFormat internalFormat, int width, int height, enumerators::TextureFormat format, enumerators::DataType dataType, unsigned char* data, bool throwOnError = false);
                    static void SetCompareFunc(enumerators::TargetTexture targetTexture, enumerators::TextureCompareFunc compareFunc, bool throwOnError = false);
                    static void SetCompareMode(enumerators::TargetTexture targetTexture, enumerators::TextureCompareMode compareMode, bool throwOnError = false);
                    static void SetMinificationFilter(enumerators::TargetTexture targetTexture, enumerators::MinificationFilterValue filterValue, bool throwOnError = false);
                    static void SetMagnificationFilter(enumerators::TargetTexture targetTexture, enumerators::MagnificationFilterValue filterValue, bool throwOnError = false);
                    static void SetWrapModeS(enumerators::TargetTexture targetTexture, enumerators::TextureWrapMode wrapMode, bool throwOnError = false);
                    static void SetWrapModeT(enumerators::TargetTexture targetTexture, enumerators::TextureWrapMode wrapMode, bool throwOnError = false);
                    static void Unbind(enumerators::TargetTexture targetTexture, bool throwOnError = false);
                };
            }
        }
    }
}
