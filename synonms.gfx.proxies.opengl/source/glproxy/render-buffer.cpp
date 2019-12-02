#include "render-buffer.h"

#include <GL\glew.h>

#include <glproxy\error.h>

using namespace synonms::gfx::proxies::opengl;
using namespace synonms::gfx::proxies::opengl::enumerators;

RenderBuffer::RenderBuffer()
{
    glGenRenderbuffers(1, &_renderBufferId);
}

RenderBuffer::RenderBuffer(RenderBuffer&& other) noexcept
    : _renderBufferId(std::exchange(other._renderBufferId, 0))
{
}

RenderBuffer& RenderBuffer::operator=(RenderBuffer&& other) noexcept
{
    _renderBufferId = std::exchange(other._renderBufferId, 0);

    return *this;
}

RenderBuffer::~RenderBuffer()
{
    if (_renderBufferId > 0) {
        glDeleteRenderbuffers(1, &_renderBufferId);
    }
}


void RenderBuffer::Allocate(TextureInternalFormat internalFormat, int width, int height, bool throwOnError) const
{
    glRenderbufferStorage(GL_RENDERBUFFER, static_cast<unsigned int>(internalFormat), width, height);
}

void RenderBuffer::Bind(bool throwOnError) const
{
    glBindRenderbuffer(GL_RENDERBUFFER, _renderBufferId);
}
