#pragma once

namespace synonms
{
    namespace gfx
    {
        namespace api
        {
            namespace opengl
            {
                namespace enumerators
                {
                    enum class TargetBuffer : unsigned int
                    {
                        ArrayBuffer = 0x8892,
                        CopyReadBuffer = 0x8F36,
                        CopyWriteBuffer = 0x8F37,
                        ElementArrayBuffer = 0x8893,
                        PixelPackBuffer = 0x88EB,
                        PixelUnpackBuffer = 0x88EC,
                        TextureBuffer = 0x8C2A,
                        TransformFeedbackBuffer = 0x8C8E,
                        UniformBuffer = 0x8A11
                    };
                }
            }
        }
    }
}
