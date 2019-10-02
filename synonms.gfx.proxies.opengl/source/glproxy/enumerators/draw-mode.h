#pragma once

namespace synonms
{
    namespace gfx
    {
        namespace proxies
        {
            namespace opengl
            {
                namespace enumerators
                {
                    enum class DrawMode : unsigned int
                    {
                        Points = 0x0000,
                        LineStrip = 0x0003,
                        LineLoop = 0x0002,
                        Lines = 0x0001,
                        LineStripAdjacency = 0x000B,
                        LinesAdjacency = 0x000A,
                        TriangleStrip = 0x0005,
                        TriangleFan = 0x0006,
                        Triangles = 0x0004,
                        TriangleStripAdjacency = 0x000D,
                        TrianglesAdjacency = 0x000C,
                        Patches = 0xE
                    };
                }
            }
        }
    }
}