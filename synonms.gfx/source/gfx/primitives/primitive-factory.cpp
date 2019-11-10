#include "primitive-factory.h"

#include <gfx\primitives\vertex-definition.h>

using namespace synonms::gfx::enumerators;
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

    float vertexData[] = {
        //    x           y       z     nx    ny    nz    u     v
        -halfWidth, -halfHeight, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
         halfWidth, -halfHeight, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f,
         halfWidth,  halfHeight, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f,
         halfWidth,  halfHeight, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f,
        -halfWidth,  halfHeight, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f,
        -halfWidth, -halfHeight, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
    };

    // TODO - Solve problem re indexed vertices needing different normals for different faces, otherwise indexes are pointless
    unsigned int indexData[] = {
        0, 1, 2,
        3, 4, 5
    };

    VertexDefinition vertexDefinition({
        VertexAttribute(AttributeType::Position, DataType::Float, 3, sizeof(float), false),
        VertexAttribute(AttributeType::Normal, DataType::Float, 3, sizeof(float), false ),
        VertexAttribute(AttributeType::TextureCoordinates, DataType::Float, 2, sizeof(float), false )
        });

    return Mesh(vertexDefinition, vertexData, 3 * 2, indexData, 3 * 2);
}

Mesh PrimitiveFactory::CreateBox(float width, float height, float depth)
{
    const auto& halfWidth = width / 2.0f;
    const auto& halfHeight = height / 2.0f;
    const auto& halfDepth = depth / 2.0f;

    float vertexData[] = {
        //    x           y          z       nx    ny    nz    u     v
        // FRONT
        -halfWidth, -halfHeight, halfDepth, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
         halfWidth, -halfHeight, halfDepth, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f,
         halfWidth,  halfHeight, halfDepth, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f,
         halfWidth,  halfHeight, halfDepth, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f,
        -halfWidth,  halfHeight, halfDepth, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f,
        -halfWidth, -halfHeight, halfDepth, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,

        // BACK
         halfWidth, -halfHeight, -halfDepth, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f,
        -halfWidth, -halfHeight, -halfDepth, 0.0f, 0.0f, -1.0f, 1.0f, 0.0f,
        -halfWidth,  halfHeight, -halfDepth, 0.0f, 0.0f, -1.0f, 1.0f, 1.0f,
        -halfWidth,  halfHeight, -halfDepth, 0.0f, 0.0f, -1.0f, 1.0f, 1.0f,
         halfWidth,  halfHeight, -halfDepth, 0.0f, 0.0f, -1.0f, 0.0f, 1.0f,
         halfWidth, -halfHeight, -halfDepth, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f,

         // TOP
        -halfWidth,  halfHeight,  halfDepth, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f,
         halfWidth,  halfHeight,  halfDepth, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,
         halfWidth,  halfHeight, -halfDepth, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f,
         halfWidth,  halfHeight, -halfDepth, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f,
        -halfWidth,  halfHeight, -halfDepth, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
        -halfWidth,  halfHeight,  halfDepth, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f,

         // BOTTOM
         halfWidth,  -halfHeight,  halfDepth, 0.0f, -1.0f, 0.0f, 0.0f, 0.0f,
        -halfWidth,  -halfHeight,  halfDepth, 0.0f, -1.0f, 0.0f, 1.0f, 0.0f,
        -halfWidth,  -halfHeight, -halfDepth, 0.0f, -1.0f, 0.0f, 1.0f, 1.0f,
        -halfWidth,  -halfHeight, -halfDepth, 0.0f, -1.0f, 0.0f, 1.0f, 1.0f,
         halfWidth,  -halfHeight, -halfDepth, 0.0f, -1.0f, 0.0f, 0.0f, 1.0f,
         halfWidth,  -halfHeight,  halfDepth, 0.0f, -1.0f, 0.0f, 0.0f, 0.0f,

         // LEFT
        -halfWidth, -halfHeight, -halfDepth, -1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
        -halfWidth, -halfHeight,  halfDepth, -1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
        -halfWidth,  halfHeight,  halfDepth, -1.0f, 0.0f, 0.0f, 1.0f, 1.0f,
        -halfWidth,  halfHeight,  halfDepth, -1.0f, 0.0f, 0.0f, 1.0f, 1.0f,
        -halfWidth,  halfHeight, -halfDepth, -1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
        -halfWidth, -halfHeight, -halfDepth, -1.0f, 0.0f, 0.0f, 0.0f, 0.0f,

         // RIGHT
         halfWidth, -halfHeight,  halfDepth, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
         halfWidth, -halfHeight, -halfDepth, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
         halfWidth,  halfHeight, -halfDepth, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f,
         halfWidth,  halfHeight, -halfDepth, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f,
         halfWidth,  halfHeight,  halfDepth, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
         halfWidth, -halfHeight,  halfDepth, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
    };

    unsigned int indexData[] = {
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

    VertexDefinition vertexDefinition({
        VertexAttribute(AttributeType::Position, DataType::Float, 3, sizeof(float), false),
        VertexAttribute(AttributeType::Normal, DataType::Float, 3, sizeof(float), false),
        VertexAttribute(AttributeType::TextureCoordinates, DataType::Float, 2, sizeof(float), false)
        });

    return Mesh(vertexDefinition, vertexData, 3 * 2 * 6, indexData, 3 * 2 * 6);
}