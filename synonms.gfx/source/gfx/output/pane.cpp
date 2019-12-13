#include "pane.h"

#include <opengl\window.h>

using namespace synonms::gfx::output;
using namespace synonms::gfx::primitives;
using namespace synonms::gfx::api;

Pane::Pane(int leftPixels, int bottomPixels, int widthPixels, int heightPixels)
    : _leftPixels(leftPixels)
    , _bottomPixels(bottomPixels)
    , _widthPixels(widthPixels)
    , _heightPixels(heightPixels)
{
}

void Pane::Resize(int leftPixels, int bottomPixels, int widthPixels, int heightPixels)
{
    _leftPixels = leftPixels;
    _bottomPixels = bottomPixels;
    _widthPixels = widthPixels;
    _heightPixels = heightPixels;
}

void Pane::SetAsViewport() const
{
    opengl::Window::SetViewport(_leftPixels, _bottomPixels, _widthPixels, _heightPixels);
}
