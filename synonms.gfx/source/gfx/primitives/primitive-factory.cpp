#include "primitive-factory.h"

#include <gfx/primitives/vertex.h>

#include <vector>

using namespace synonms::gfx::primitives;

// OpenGL is right handed (+x - thumb, y - pointer, z - middle)
// +x to right
// +y to sky
// +z to viewer

// Faces drawn Anti-Clockwise
//      2
//    / |
//   0--1

Mesh PrimitiveFactory::CreatePlane(float width, float height)
{
    const auto& halfWidth = width / 2.0f;
    const auto& halfHeight = height / 2.0f;

    auto vertices = std::vector<Vertex> {
        //    x           y         z       nx    ny    nz      u     v
        {{-halfWidth, -halfHeight, 0.0f}, {0.0f, 0.0f, 1.0f}, {0.0f, 0.0f}},
        {{ halfWidth, -halfHeight, 0.0f}, {0.0f, 0.0f, 1.0f}, {1.0f, 0.0f}},
        {{ halfWidth,  halfHeight, 0.0f}, {0.0f, 0.0f, 1.0f}, {1.0f, 1.0f}},
        {{ halfWidth,  halfHeight, 0.0f}, {0.0f, 0.0f, 1.0f}, {1.0f, 1.0f}},
        {{-halfWidth,  halfHeight, 0.0f}, {0.0f, 0.0f, 1.0f}, {0.0f, 1.0f}},
        {{-halfWidth, -halfHeight, 0.0f}, {0.0f, 0.0f, 1.0f}, {0.0f, 0.0f}}
    };

    // TODO - Solve problem re indexed vertices needing different normals for different faces, otherwise indexes are pointless
    auto indices = std::vector<unsigned int> {
        0, 1, 2,
        3, 4, 5
    };

    return Mesh(vertices, indices);
}

Mesh PrimitiveFactory::CreateBox(float width, float height, float depth)
{
    const auto& halfWidth = width / 2.0f;
    const auto& halfHeight = height / 2.0f;
    const auto& halfDepth = depth / 2.0f;

    auto vertices = std::vector<Vertex>{
        //    x           y             z            nx    ny      nz    u     v
        // FRONT
        {{-halfWidth, -halfHeight,  halfDepth}, { 0.0f,  0.0f,  1.0f}, {0.0f, 0.0f}},
        {{ halfWidth, -halfHeight,  halfDepth}, { 0.0f,  0.0f,  1.0f}, {1.0f, 0.0f}},
        {{ halfWidth,  halfHeight,  halfDepth}, { 0.0f,  0.0f,  1.0f}, {1.0f, 1.0f}},
        {{ halfWidth,  halfHeight,  halfDepth}, { 0.0f,  0.0f,  1.0f}, {1.0f, 1.0f}},
        {{-halfWidth,  halfHeight,  halfDepth}, { 0.0f,  0.0f,  1.0f}, {0.0f, 1.0f}},
        {{-halfWidth, -halfHeight,  halfDepth}, { 0.0f,  0.0f,  1.0f}, {0.0f, 0.0f}},

        // BACK
        {{ halfWidth, -halfHeight, -halfDepth}, { 0.0f,  0.0f, -1.0f}, {0.0f, 0.0f}},
        {{-halfWidth, -halfHeight, -halfDepth}, { 0.0f,  0.0f, -1.0f}, {1.0f, 0.0f}},
        {{-halfWidth,  halfHeight, -halfDepth}, { 0.0f,  0.0f, -1.0f}, {1.0f, 1.0f}},
        {{-halfWidth,  halfHeight, -halfDepth}, { 0.0f,  0.0f, -1.0f}, {1.0f, 1.0f}},
        {{ halfWidth,  halfHeight, -halfDepth}, { 0.0f,  0.0f, -1.0f}, {0.0f, 1.0f}},
        {{ halfWidth, -halfHeight, -halfDepth}, { 0.0f,  0.0f, -1.0f}, {0.0f, 0.0f}},

        // TOP 
        {{-halfWidth,  halfHeight,  halfDepth}, { 0.0f,  1.0f,  0.0f}, {0.0f, 0.0f}},
        {{ halfWidth,  halfHeight,  halfDepth}, { 0.0f,  1.0f,  0.0f}, {1.0f, 0.0f}},
        {{ halfWidth,  halfHeight, -halfDepth}, { 0.0f,  1.0f,  0.0f}, {1.0f, 1.0f}},
        {{ halfWidth,  halfHeight, -halfDepth}, { 0.0f,  1.0f,  0.0f}, {1.0f, 1.0f}},
        {{-halfWidth,  halfHeight, -halfDepth}, { 0.0f,  1.0f,  0.0f}, {0.0f, 1.0f}},
        {{-halfWidth,  halfHeight,  halfDepth}, { 0.0f,  1.0f,  0.0f}, {0.0f, 0.0f}},

        // BOTTOM
        {{ halfWidth, -halfHeight,  halfDepth}, { 0.0f, -1.0f,  0.0f}, {0.0f, 0.0f}},
        {{-halfWidth, -halfHeight,  halfDepth}, { 0.0f, -1.0f,  0.0f}, {1.0f, 0.0f}},
        {{-halfWidth, -halfHeight, -halfDepth}, { 0.0f, -1.0f,  0.0f}, {1.0f, 1.0f}},
        {{-halfWidth, -halfHeight, -halfDepth}, { 0.0f, -1.0f,  0.0f}, {1.0f, 1.0f}},
        {{ halfWidth, -halfHeight, -halfDepth}, { 0.0f, -1.0f,  0.0f}, {0.0f, 1.0f}},
        {{ halfWidth, -halfHeight,  halfDepth}, { 0.0f, -1.0f,  0.0f}, {0.0f, 0.0f}},

        // LEFT
        {{-halfWidth, -halfHeight, -halfDepth}, {-1.0f,  0.0f,  0.0f}, {0.0f, 0.0f}},
        {{-halfWidth, -halfHeight,  halfDepth}, {-1.0f,  0.0f,  0.0f}, {1.0f, 0.0f}},
        {{-halfWidth,  halfHeight,  halfDepth}, {-1.0f,  0.0f,  0.0f}, {1.0f, 1.0f}},
        {{-halfWidth,  halfHeight,  halfDepth}, {-1.0f,  0.0f,  0.0f}, {1.0f, 1.0f}},
        {{-halfWidth,  halfHeight, -halfDepth}, {-1.0f,  0.0f,  0.0f}, {0.0f, 1.0f}},
        {{-halfWidth, -halfHeight, -halfDepth}, {-1.0f,  0.0f,  0.0f}, {0.0f, 0.0f}},

        // RIGHT
        {{ halfWidth, -halfHeight,  halfDepth}, { 1.0f,  0.0f,  0.0f}, {0.0f, 0.0f}},
        {{ halfWidth, -halfHeight, -halfDepth}, { 1.0f,  0.0f,  0.0f}, {1.0f, 0.0f}},
        {{ halfWidth,  halfHeight, -halfDepth}, { 1.0f,  0.0f,  0.0f}, {1.0f, 1.0f}},
        {{ halfWidth,  halfHeight, -halfDepth}, { 1.0f,  0.0f,  0.0f}, {1.0f, 1.0f}},
        {{ halfWidth,  halfHeight,  halfDepth}, { 1.0f,  0.0f,  0.0f}, {0.0f, 1.0f}},
        {{ halfWidth, -halfHeight,  halfDepth}, { 1.0f,  0.0f,  0.0f}, {0.0f, 0.0f}}
    };

    auto indices = std::vector<unsigned int>{
         0,  1,  2,
         3,  4,  5,
         6,  7,  8,
         9, 10, 11,
        12, 13, 14,
        15, 16, 17,
        18, 19, 20,
        21, 22, 23,
        24, 25, 26,
        27, 28, 29,
        30, 31, 32,
        33, 34, 35,
    };

    return Mesh(vertices, indices);
}