#include "render-buffer-factory.h"

using namespace synonms::gfx::api::opengl;
using namespace synonms::gfx::api::opengl::factories;

std::unique_ptr<RenderBuffer> RenderBufferFactory::CreateDepthStencilBuffer(int width, int height)
{
    auto result = std::make_unique<opengl::RenderBuffer>();
    result->Bind();
    result->Allocate(opengl::enumerators::TextureInternalFormat::Depth24Stencil8, width, height);

    return std::move(result);
}
