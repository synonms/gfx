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
                    // STREAM: The data store contents will be modified onceand used at most a few times.
                    // STATIC: The data store contents will be modified onceand used many times.
                    // DYNAMIC: The data store contents will be modified repeatedlyand used many times.
                    // DRAW: The data store contents are modified by the application, and used as the source for GL drawingand image specification commands.
                    // READ: The data store contents are modified by reading data from the GL, and used to return that data when queried by the application.
                    // COPY: The data store contents are modified by reading data from the GL, and used as the source for GL drawingand image specification commands.
                    enum class DataUsage : unsigned int
                    {
                        StreamDraw = 0x88E0,
                        StreamRead = 0x88E1,
                        StreamCopy = 0x88E2,
                        StaticDraw = 0x88E4,
                        StaticRead = 0x88E5,
                        StaticCopy = 0x88E6,
                        DynamicDraw = 0x88E8,
                        DynamicRead = 0x88E9,
                        DynamicCopy = 0x88EA
                    };
                }
            }
        }
    }
}
