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

// Tangent, Bitangent and Normal form axes in tangent space
// Bitangent can be calulated in shader as cross of normal and tangent
// Consider Normal as the Z axis (right handed), then set Tangent as X axis


std::shared_ptr<Mesh> PrimitiveFactory::CreatePlane(float width, float height)
{
    const auto& halfWidth = width / 2.0f;
    const auto& halfHeight = height / 2.0f;

    auto vertices = std::vector<Vertex> {
        //    x           y         z       nx    ny    nz      u     v       tx    ty    tz
        {{-halfWidth, -halfHeight, 0.0f}, {0.0f, 0.0f, 1.0f}, {0.0f, 0.0f}, {1.0f, 0.0f, 0.0f}},
        {{ halfWidth, -halfHeight, 0.0f}, {0.0f, 0.0f, 1.0f}, {1.0f, 0.0f}, {1.0f, 0.0f, 0.0f}},
        {{ halfWidth,  halfHeight, 0.0f}, {0.0f, 0.0f, 1.0f}, {1.0f, 1.0f}, {1.0f, 0.0f, 0.0f}},
        {{ halfWidth,  halfHeight, 0.0f}, {0.0f, 0.0f, 1.0f}, {1.0f, 1.0f}, {1.0f, 0.0f, 0.0f}},
        {{-halfWidth,  halfHeight, 0.0f}, {0.0f, 0.0f, 1.0f}, {0.0f, 1.0f}, {1.0f, 0.0f, 0.0f}},
        {{-halfWidth, -halfHeight, 0.0f}, {0.0f, 0.0f, 1.0f}, {0.0f, 0.0f}, {1.0f, 0.0f, 0.0f}}
    };

    // TODO - Solve problem re indexed vertices needing different normals for different faces, otherwise indexes are pointless
    auto indices = std::vector<unsigned int> {
        0, 1, 2,
        3, 4, 5
    };

    return std::make_shared<Mesh>(vertices, indices);
}

std::shared_ptr<Mesh> PrimitiveFactory::CreatePlane(float left, float bottom, float width, float height)
{
    const auto& right = left + width;
    const auto& top = bottom + height;

    auto vertices = std::vector<Vertex>{
        // x       y      z       nx    ny    nz      u     v       tx    ty    tz
        {{left,  bottom, 0.0f}, {0.0f, 0.0f, 1.0f}, {0.0f, 0.0f}, {1.0f, 0.0f, 0.0f}},
        {{right, bottom, 0.0f}, {0.0f, 0.0f, 1.0f}, {1.0f, 0.0f}, {1.0f, 0.0f, 0.0f}},
        {{right, top,    0.0f}, {0.0f, 0.0f, 1.0f}, {1.0f, 1.0f}, {1.0f, 0.0f, 0.0f}},
        {{right, top,    0.0f}, {0.0f, 0.0f, 1.0f}, {1.0f, 1.0f}, {1.0f, 0.0f, 0.0f}},
        {{left,  top,    0.0f}, {0.0f, 0.0f, 1.0f}, {0.0f, 1.0f}, {1.0f, 0.0f, 0.0f}},
        {{left,  bottom, 0.0f}, {0.0f, 0.0f, 1.0f}, {0.0f, 0.0f}, {1.0f, 0.0f, 0.0f}}
    };

    // TODO - Solve problem re indexed vertices needing different normals for different faces, otherwise indexes are pointless
    auto indices = std::vector<unsigned int>{
        0, 1, 2,
        3, 4, 5
    };

    return std::make_shared<Mesh>(vertices, indices);
}

std::shared_ptr<Mesh> PrimitiveFactory::CreateBox(float width, float height, float depth)
{
    const auto& halfWidth = width / 2.0f;
    const auto& halfHeight = height / 2.0f;
    const auto& halfDepth = depth / 2.0f;

    auto vertices = std::vector<Vertex>{
        //    x           y             z            nx    ny      nz    u     v          tx    ty    tz
        // FRONT
        {{-halfWidth, -halfHeight,  halfDepth}, { 0.0f,  0.0f,  1.0f}, {0.25f, 0.333f}, {1.0f, 0.0f, 0.0f}},
        {{ halfWidth, -halfHeight,  halfDepth}, { 0.0f,  0.0f,  1.0f}, {0.5f,  0.333f}, {1.0f, 0.0f, 0.0f}},
        {{ halfWidth,  halfHeight,  halfDepth}, { 0.0f,  0.0f,  1.0f}, {0.5f,  0.666f}, {1.0f, 0.0f, 0.0f}},
        {{ halfWidth,  halfHeight,  halfDepth}, { 0.0f,  0.0f,  1.0f}, {0.5f,  0.666f}, {1.0f, 0.0f, 0.0f}},
        {{-halfWidth,  halfHeight,  halfDepth}, { 0.0f,  0.0f,  1.0f}, {0.25f, 0.666f}, {1.0f, 0.0f, 0.0f}},
        {{-halfWidth, -halfHeight,  halfDepth}, { 0.0f,  0.0f,  1.0f}, {0.25f, 0.333f}, {1.0f, 0.0f, 0.0f}},

        // BACK
        {{ halfWidth, -halfHeight, -halfDepth}, { 0.0f,  0.0f, -1.0f}, {0.75f, 0.333f}, {-1.0f, 0.0f, 0.0f}},
        {{-halfWidth, -halfHeight, -halfDepth}, { 0.0f,  0.0f, -1.0f}, {1.0f,  0.333f}, {-1.0f, 0.0f, 0.0f}},
        {{-halfWidth,  halfHeight, -halfDepth}, { 0.0f,  0.0f, -1.0f}, {1.0f,  0.666f}, {-1.0f, 0.0f, 0.0f}},
        {{-halfWidth,  halfHeight, -halfDepth}, { 0.0f,  0.0f, -1.0f}, {1.0f,  0.666f}, {-1.0f, 0.0f, 0.0f}},
        {{ halfWidth,  halfHeight, -halfDepth}, { 0.0f,  0.0f, -1.0f}, {0.75f, 0.666f}, {-1.0f, 0.0f, 0.0f}},
        {{ halfWidth, -halfHeight, -halfDepth}, { 0.0f,  0.0f, -1.0f}, {0.75f, 0.333f}, {-1.0f, 0.0f, 0.0f}},

        // TOP 
        {{-halfWidth,  halfHeight,  halfDepth}, { 0.0f,  1.0f,  0.0f}, {0.25f, 0.666f}, {1.0f, 0.0f, 0.0f}},
        {{ halfWidth,  halfHeight,  halfDepth}, { 0.0f,  1.0f,  0.0f}, {0.5f,  0.666f}, {1.0f, 0.0f, 0.0f}},
        {{ halfWidth,  halfHeight, -halfDepth}, { 0.0f,  1.0f,  0.0f}, {0.5f,  1.0f  }, {1.0f, 0.0f, 0.0f}},
        {{ halfWidth,  halfHeight, -halfDepth}, { 0.0f,  1.0f,  0.0f}, {0.5f,  1.0f  }, {1.0f, 0.0f, 0.0f}},
        {{-halfWidth,  halfHeight, -halfDepth}, { 0.0f,  1.0f,  0.0f}, {0.25f, 1.0f  }, {1.0f, 0.0f, 0.0f}},
        {{-halfWidth,  halfHeight,  halfDepth}, { 0.0f,  1.0f,  0.0f}, {0.25f, 0.666f}, {1.0f, 0.0f, 0.0f}},

        // BOTTOM
        {{ halfWidth, -halfHeight,  halfDepth}, { 0.0f, -1.0f,  0.0f}, {0.25f, 0.0f  }, {1.0f, 0.0f, 0.0f}},
        {{-halfWidth, -halfHeight,  halfDepth}, { 0.0f, -1.0f,  0.0f}, {0.5f,  0.0f  }, {1.0f, 0.0f, 0.0f}},
        {{-halfWidth, -halfHeight, -halfDepth}, { 0.0f, -1.0f,  0.0f}, {0.5f,  0.333f}, {1.0f, 0.0f, 0.0f}},
        {{-halfWidth, -halfHeight, -halfDepth}, { 0.0f, -1.0f,  0.0f}, {0.5f,  0.333f}, {1.0f, 0.0f, 0.0f}},
        {{ halfWidth, -halfHeight, -halfDepth}, { 0.0f, -1.0f,  0.0f}, {0.25f, 0.333f}, {1.0f, 0.0f, 0.0f}},
        {{ halfWidth, -halfHeight,  halfDepth}, { 0.0f, -1.0f,  0.0f}, {0.25f, 0.0f  }, {1.0f, 0.0f, 0.0f}},

        // LEFT
        {{-halfWidth, -halfHeight, -halfDepth}, {-1.0f,  0.0f,  0.0f}, {0.0f,  0.333f}, {0.0f, 0.0f, 1.0f}},
        {{-halfWidth, -halfHeight,  halfDepth}, {-1.0f,  0.0f,  0.0f}, {0.25f, 0.333f}, {0.0f, 0.0f, 1.0f}},
        {{-halfWidth,  halfHeight,  halfDepth}, {-1.0f,  0.0f,  0.0f}, {0.25f, 0.666f}, {0.0f, 0.0f, 1.0f}},
        {{-halfWidth,  halfHeight,  halfDepth}, {-1.0f,  0.0f,  0.0f}, {0.25f, 0.666f}, {0.0f, 0.0f, 1.0f}},
        {{-halfWidth,  halfHeight, -halfDepth}, {-1.0f,  0.0f,  0.0f}, {0.0f,  0.666f}, {0.0f, 0.0f, 1.0f}},
        {{-halfWidth, -halfHeight, -halfDepth}, {-1.0f,  0.0f,  0.0f}, {0.0f,  0.333f}, {0.0f, 0.0f, 1.0f}},

        // RIGHT
        {{ halfWidth, -halfHeight,  halfDepth}, { 1.0f,  0.0f,  0.0f}, {0.5f,  0.333f}, {0.0f, 0.0f, -1.0f}},
        {{ halfWidth, -halfHeight, -halfDepth}, { 1.0f,  0.0f,  0.0f}, {0.75f, 0.333f}, {0.0f, 0.0f, -1.0f}},
        {{ halfWidth,  halfHeight, -halfDepth}, { 1.0f,  0.0f,  0.0f}, {0.75f, 0.666f}, {0.0f, 0.0f, -1.0f}},
        {{ halfWidth,  halfHeight, -halfDepth}, { 1.0f,  0.0f,  0.0f}, {0.75f, 0.666f}, {0.0f, 0.0f, -1.0f}},
        {{ halfWidth,  halfHeight,  halfDepth}, { 1.0f,  0.0f,  0.0f}, {0.5f,  0.666f}, {0.0f, 0.0f, -1.0f}},
        {{ halfWidth, -halfHeight,  halfDepth}, { 1.0f,  0.0f,  0.0f}, {0.5f,  0.333f}, {0.0f, 0.0f, -1.0f}}
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

    return std::make_shared<Mesh>(vertices, indices);
}

std::shared_ptr<Mesh> PrimitiveFactory::CreateSkyBox()
{
    const float width = 1.0f;
    const float height = 1.0f;
    const float depth = 1.0f;
    const auto& halfWidth = width / 2.0f;
    const auto& halfHeight = height / 2.0f;
    const auto& halfDepth = depth / 2.0f;

    auto vertices = std::vector<Vertex>{
        //    x           y             z          nx    ny      nz    u     v          tx    ty    tz
        // BACK
        {{-halfWidth, -halfHeight, -halfDepth}, { 0.0f,  0.0f,  1.0f}, {0.0f, 0.0f}, {1.0f, 0.0f, 0.0f}},
        {{ halfWidth, -halfHeight, -halfDepth}, { 0.0f,  0.0f,  1.0f}, {1.0f, 0.0f}, {1.0f, 0.0f, 0.0f}},
        {{ halfWidth,  halfHeight, -halfDepth}, { 0.0f,  0.0f,  1.0f}, {1.0f, 1.0f}, {1.0f, 0.0f, 0.0f}},
        {{ halfWidth,  halfHeight, -halfDepth}, { 0.0f,  0.0f,  1.0f}, {1.0f, 1.0f}, {1.0f, 0.0f, 0.0f}},
        {{-halfWidth,  halfHeight, -halfDepth}, { 0.0f,  0.0f,  1.0f}, {0.0f, 1.0f}, {1.0f, 0.0f, 0.0f}},
        {{-halfWidth, -halfHeight, -halfDepth}, { 0.0f,  0.0f,  1.0f}, {0.0f, 0.0f}, {1.0f, 0.0f, 0.0f}},

        // FRONT
        {{ halfWidth, -halfHeight,  halfDepth}, { 0.0f,  0.0f, -1.0f}, {0.0f, 0.0f}, {-1.0f, 0.0f, 0.0f}},
        {{-halfWidth, -halfHeight,  halfDepth}, { 0.0f,  0.0f, -1.0f}, {0.0f, 0.0f}, {-1.0f, 0.0f, 0.0f}},
        {{-halfWidth,  halfHeight,  halfDepth}, { 0.0f,  0.0f, -1.0f}, {0.0f, 0.0f}, {-1.0f, 0.0f, 0.0f}},
        {{-halfWidth,  halfHeight,  halfDepth}, { 0.0f,  0.0f, -1.0f}, {0.0f, 0.0f}, {-1.0f, 0.0f, 0.0f}},
        {{ halfWidth,  halfHeight,  halfDepth}, { 0.0f,  0.0f, -1.0f}, {0.0f, 0.0f}, {-1.0f, 0.0f, 0.0f}},
        {{ halfWidth, -halfHeight,  halfDepth}, { 0.0f,  0.0f, -1.0f}, {0.0f, 0.0f}, {-1.0f, 0.0f, 0.0f}},

        // BOTTOM
        {{-halfWidth, -halfHeight,  halfDepth}, { 0.0f,  1.0f,  0.0f}, {0.0f, 0.0f}, {1.0f, 0.0f, 0.0f}},
        {{ halfWidth, -halfHeight,  halfDepth}, { 0.0f,  1.0f,  0.0f}, {0.0f, 0.0f}, {1.0f, 0.0f, 0.0f}},
        {{ halfWidth, -halfHeight, -halfDepth}, { 0.0f,  1.0f,  0.0f}, {0.0f, 0.0f}, {1.0f, 0.0f, 0.0f}},
        {{ halfWidth, -halfHeight, -halfDepth}, { 0.0f,  1.0f,  0.0f}, {0.0f, 0.0f}, {1.0f, 0.0f, 0.0f}},
        {{-halfWidth, -halfHeight, -halfDepth}, { 0.0f,  1.0f,  0.0f}, {0.0f, 0.0f}, {1.0f, 0.0f, 0.0f}},
        {{-halfWidth, -halfHeight,  halfDepth}, { 0.0f,  1.0f,  0.0f}, {0.0f, 0.0f}, {1.0f, 0.0f, 0.0f}},

        // TOP
        {{ halfWidth,  halfHeight,  halfDepth}, { 0.0f, -1.0f,  0.0f}, {0.0f, 0.0f}, {1.0f, 0.0f, 0.0f}},
        {{-halfWidth,  halfHeight,  halfDepth}, { 0.0f, -1.0f,  0.0f}, {0.0f, 0.0f}, {1.0f, 0.0f, 0.0f}},
        {{-halfWidth,  halfHeight, -halfDepth}, { 0.0f, -1.0f,  0.0f}, {0.0f, 0.0f}, {1.0f, 0.0f, 0.0f}},
        {{-halfWidth,  halfHeight, -halfDepth}, { 0.0f, -1.0f,  0.0f}, {0.0f, 0.0f}, {1.0f, 0.0f, 0.0f}},
        {{ halfWidth,  halfHeight, -halfDepth}, { 0.0f, -1.0f,  0.0f}, {0.0f, 0.0f}, {1.0f, 0.0f, 0.0f}},
        {{ halfWidth,  halfHeight,  halfDepth}, { 0.0f, -1.0f,  0.0f}, {0.0f, 0.0f}, {1.0f, 0.0f, 0.0f}},

        // RIGHT
        {{ halfWidth, -halfHeight, -halfDepth}, {-1.0f,  0.0f,  0.0f}, {0.0f, 0.0f}, {0.0f, 0.0f, 1.0f}},
        {{ halfWidth, -halfHeight,  halfDepth}, {-1.0f,  0.0f,  0.0f}, {0.0f, 0.0f}, {0.0f, 0.0f, 1.0f}},
        {{ halfWidth,  halfHeight,  halfDepth}, {-1.0f,  0.0f,  0.0f}, {0.0f, 0.0f}, {0.0f, 0.0f, 1.0f}},
        {{ halfWidth,  halfHeight,  halfDepth}, {-1.0f,  0.0f,  0.0f}, {0.0f, 0.0f}, {0.0f, 0.0f, 1.0f}},
        {{ halfWidth,  halfHeight, -halfDepth}, {-1.0f,  0.0f,  0.0f}, {0.0f, 0.0f}, {0.0f, 0.0f, 1.0f}},
        {{ halfWidth, -halfHeight, -halfDepth}, {-1.0f,  0.0f,  0.0f}, {0.0f, 0.0f}, {0.0f, 0.0f, 1.0f}},

        // LEFT
        {{-halfWidth, -halfHeight,  halfDepth}, { 1.0f,  0.0f,  0.0f}, {0.0f, 0.0f}, {0.0f, 0.0f, -1.0f}},
        {{-halfWidth, -halfHeight, -halfDepth}, { 1.0f,  0.0f,  0.0f}, {0.0f, 0.0f}, {0.0f, 0.0f, -1.0f}},
        {{-halfWidth,  halfHeight, -halfDepth}, { 1.0f,  0.0f,  0.0f}, {0.0f, 0.0f}, {0.0f, 0.0f, -1.0f}},
        {{-halfWidth,  halfHeight, -halfDepth}, { 1.0f,  0.0f,  0.0f}, {0.0f, 0.0f}, {0.0f, 0.0f, -1.0f}},
        {{-halfWidth,  halfHeight,  halfDepth}, { 1.0f,  0.0f,  0.0f}, {0.0f, 0.0f}, {0.0f, 0.0f, -1.0f}},
        {{-halfWidth, -halfHeight,  halfDepth}, { 1.0f,  0.0f,  0.0f}, {0.0f, 0.0f}, {0.0f, 0.0f, -1.0f}}
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

    return std::make_shared<Mesh>(vertices, indices);
}              