#include "vertex-definition.h"

#include <numeric>

using namespace synonms::gfx::primitives;

VertexDefinition::VertexDefinition(std::vector<VertexAttribute>&& attributes)
    : _attributes(std::move(attributes))
{
}

const std::vector<VertexAttribute>& VertexDefinition::GetAttributes() const
{
    return _attributes;
}

int VertexDefinition::Size() const
{
    return std::accumulate(std::begin(_attributes), std::end(_attributes), 0, [](int runningTotal, const VertexAttribute& attribute) { 
        return runningTotal += attribute.GetNoOfBytes(); 
    });
}
