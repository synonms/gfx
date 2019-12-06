#include "render-buffer.h"

#include <GL\glew.h>

#include <utility>

using namespace synonms::gfx::api::opengl;
using namespace synonms::gfx::api::opengl::enumerators;

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


void RenderBuffer::Allocate(TextureInternalFormat internalFormat, int width, int height) const
{
    glRenderbufferStorage(GL_RENDERBUFFER, static_cast<unsigned int>(internalFormat), width, height);
}

void RenderBuffer::Bind() const
{
    glBindRenderbuffer(GL_RENDERBUFFER, _renderBufferId);
}
