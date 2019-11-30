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
                    enum class FramebufferStatus : unsigned int
                    {
                        Complete = 0x8CD5,
                        Undefined = 0x8219,
                        IncompleteAttachment = 0x8CD6,
                        IncompleteMissingAttachment = 0x8CD7,
                        IncompleteDrawBuffer = 0x8CDB,
                        IncompleteReadBuffer = 0x8CDC,
                        Unsupported = 0x8CDD,
                        IncompleteMultisample = 0x8D56,
                        IncompleteLayerTargets = 0x8DA8
                    };
                }
            }
        }
    }
}




