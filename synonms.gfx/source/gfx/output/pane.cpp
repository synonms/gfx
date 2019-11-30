#include "pane.h"

#include <gfx\primitives\primitive-factory.h>

using namespace synonms::gfx::output;
using namespace synonms::gfx::primitives;

Pane::Pane(float left, float bottom, float width, float height)
    : _left(left)
    , _bottom(bottom)
    , _width(width)
    , _height(height)
    , _mesh(std::move(PrimitiveFactory::CreatePlane(left, bottom, width, height)))
{
}
