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
                    // NOTE: Any GLFW_ enties must have the hex value assigned before use
                    enum class WindowHintInt : int
                    {
                        ContextVersionMajor = 0x00022002,
                        ContextVersionMinor = 0x00022003,
                        OpenGLProfile = 0x00022008     // GLFW_OPENGL_CORE_PROFILE, GLFW_OPENGL_COMPAT_PROFILE or GLFW_OPENGL_ANY_PROFILE

                        //GLFW_RESIZABLE,                 // bool
                        //GLFW_VISIBLE,                   // bool
                        //GLFW_DECORATED,                 // bool
                        //GLFW_FOCUSED,                   // bool
                        //GLFW_AUTO_ICONIFY,              // bool
                        //GLFW_FLOATING,                  // bool
                        //GLFW_MAXIMIZED,                 // bool
                        //GLFW_CENTER_CURSOR,             // bool
                        //GLFW_TRANSPARENT_FRAMEBUFFER,   // bool
                        //GLFW_FOCUS_ON_SHOW,             // bool
                        //GLFW_SCALE_TO_MONITOR,          // bool

                        //GLFW_RED_BITS, GLFW_GREEN_BITS, GLFW_BLUE_BITS, GLFW_ALPHA_BITS, GLFW_DEPTH_BITS, GLFW_STENCIL_BITS,    // Default framebuffer bit depth - GLFW_DONT_CARE means ignore
                        //GLFW_ACCUM_RED_BITS, GLFW_ACCUM_GREEN_BITS, GLFW_ACCUM_BLUE_BITS, GLFW_ACCUM_ALPHA_BITS,                // Accumulation buffer bit depth - GLFW_DONT_CARE means ignore
                        //GLFW_AUX_BUFFERS,
                        //GLFW_STEREO,                    // bool
                        //GLFW_SAMPLES,
                        //GLFW_SRGB_CAPABLE,              // bool
                        //GLFW_DOUBLEBUFFER,              // bool
                        //GLFW_REFRESH_RATE,
                        //GLFW_CLIENT_API,                // GLFW_OPENGL_API, GLFW_OPENGL_ES_API or GLFW_NO_API
                        //GLFW_CONTEXT_CREATION_API,      // GLFW_NATIVE_CONTEXT_API, GLFW_EGL_CONTEXT_API or GLFW_OSMESA_CONTEXT_API
                        //GLFW_OPENGL_FORWARD_COMPAT,
                        //GLFW_OPENGL_DEBUG_CONTEXT,      // bool
                        //GLFW_CONTEXT_ROBUSTNESS,        // GLFW_NO_RESET_NOTIFICATION, GLFW_LOSE_CONTEXT_ON_RESET or GLFW_NO_ROBUSTNESS
                        //GLFW_CONTEXT_RELEASE_BEHAVIOR,  // GLFW_ANY_RELEASE_BEHAVIOR, GLFW_RELEASE_BEHAVIOR_FLUSH or GLFW_RELEASE_BEHAVIOR_NONE
                        //GLFW_CONTEXT_NO_ERROR           // bool
                    };

                    enum class WindowHintString : int
                    {
                    };
                }
            }
        }
    }
}



