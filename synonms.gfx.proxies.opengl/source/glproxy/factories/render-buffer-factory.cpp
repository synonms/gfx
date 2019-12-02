#include "render-buffer-factory.h"

using namespace synonms::gfx::proxies::opengl;
using namespace synonms::gfx::proxies::opengl::factories;

std::unique_ptr<RenderBuffer> RenderBufferFactory::CreateDepthStencilBuffer(int width, int height)
{
    auto result = std::make_unique<opengl::RenderBuffer>();
    result->Bind();
    result->Allocate(opengl::enumerators::TextureInternalFormat::GL_DEPTH24_STENCIL8, width, height);

    return std::move(result);
}
