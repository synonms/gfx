#pragma once

#include <gfx\primitives\vertex-attribute.h>

#include <vector>

namespace synonms
{
    namespace gfx 
    {
        namespace primitives 
        {
            class VertexDefinition
            {
            public:
                VertexDefinition(std::vector<VertexAttribute>&& attributes);

                const std::vector<VertexAttribute>& GetAttributes() const;
                int Size() const;

            private:
                std::vector<VertexAttribute> _attributes;
            };
        }
    }
}