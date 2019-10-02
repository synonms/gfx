#pragma once

#include <gfx\exports.h>
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
                SYNONMS_GFX_API VertexDefinition(std::vector<VertexAttribute>&& attributes);

                SYNONMS_GFX_API const std::vector<VertexAttribute>& GetAttributes() const;
                SYNONMS_GFX_API int Size() const;

            private:
                std::vector<VertexAttribute> _attributes;
            };
        }
    }
}