#pragma once

#include <glproxy\glproxy-exports.h>
#include <glproxy\enumerators\minification-filter-value.h>
#include <glproxy\enumerators\magnification-filter-value.h>
#include <glproxy\enumerators\target-texture.h>
#include <glproxy\enumerators\texture-parameter.h>
#include <glproxy\enumerators\texture-wrap-mode.h>

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
                    GLPROXY_API static void ActivateSlot(unsigned int slot, bool throwOnError = false);
                    GLPROXY_API static void Bind(enumerators::TargetTexture targetTexture, unsigned int textureId, bool throwOnError = false);
                    GLPROXY_API static void Delete(unsigned int textureId, bool throwOnError = false);
                    GLPROXY_API static unsigned int Generate(bool throwOnError = false);
                    GLPROXY_API static void SendData(enumerators::TargetTexture targetTexture, int width, int height, unsigned char* data, bool throwOnError = false);
                    GLPROXY_API static void SetMinificationFilter(enumerators::TargetTexture targetTexture, enumerators::MinificationFilterValue filterValue, bool throwOnError = false);
                    GLPROXY_API static void SetMagnificationFilter(enumerators::TargetTexture targetTexture, enumerators::MagnificationFilterValue filterValue, bool throwOnError = false);
                    GLPROXY_API static void SetWrapModeS(enumerators::TargetTexture targetTexture, enumerators::TextureWrapMode wrapMode, bool throwOnError = false);
                    GLPROXY_API static void SetWrapModeT(enumerators::TargetTexture targetTexture, enumerators::TextureWrapMode wrapMode, bool throwOnError = false);
                    GLPROXY_API static void Unbind(enumerators::TargetTexture targetTexture, bool throwOnError = false);
                };
            }
        }
    }
}
