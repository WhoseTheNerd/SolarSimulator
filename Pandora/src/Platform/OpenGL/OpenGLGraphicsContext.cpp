#include "OpenGLGraphicsContext.hpp"

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>

namespace Pandora {

    static void message_callback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, GLchar const* message, void const* user_param)
    {
        const char* src_str = nullptr;
        switch(source)
        {
        case GL_DEBUG_SOURCE_API: src_str = "API"; break;
        case GL_DEBUG_SOURCE_WINDOW_SYSTEM: src_str = "WINDOW SYSTEM"; break;
        case GL_DEBUG_SOURCE_SHADER_COMPILER: src_str = "SHADER COMPILER"; break;
        case GL_DEBUG_SOURCE_THIRD_PARTY: src_str = "THIRD PARTY"; break;
        case GL_DEBUG_SOURCE_APPLICATION: src_str = "APPLICATION"; break;
        case GL_DEBUG_SOURCE_OTHER: src_str = "OTHER"; break;
        default: src_str = "UNKNOWN"; break;
        }

        const char* type_str = nullptr;
        switch (type)
        {
        case GL_DEBUG_TYPE_ERROR: type_str = "ERROR"; break;
        case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR: type_str = "DEPRECATED_BEHAVIOR"; break;
        case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR: type_str = "UNDEFINED_BEHAVIOR"; break;
        case GL_DEBUG_TYPE_PORTABILITY: type_str = "PORTABILITY"; break;
        case GL_DEBUG_TYPE_PERFORMANCE: type_str = "PERFORMANCE"; break;
        case GL_DEBUG_TYPE_MARKER: type_str = "MARKER"; break;
        case GL_DEBUG_TYPE_OTHER: type_str = "OTHER"; break;
        default: type_str = "UNKNOWN"; break;
        }

        switch (severity)
        {
        case GL_DEBUG_SEVERITY_NOTIFICATION:
            PD_CORE_TRACE("[{0}][{1}] {2}", src_str, type_str, message);
            break;

        case GL_DEBUG_SEVERITY_LOW:
            PD_CORE_INFO("[{0}][{1}] {2}", src_str, type_str, message);
            break;

        case GL_DEBUG_SEVERITY_MEDIUM:
            PD_CORE_WARN("[{0}][{1}] {2}", src_str, type_str, message);
            break;

        case GL_DEBUG_SEVERITY_HIGH:
            PD_CORE_ERROR("[{0}][{1}] {2}", src_str, type_str, message);
            break;

        default: break;
        }
    }

    Scope<GraphicsContext> GraphicsContext::Create(GLFWwindow* window_handle)
    {
        return CreateScope<OpenGLGraphicsContext>(window_handle);
    }

    OpenGLGraphicsContext::OpenGLGraphicsContext(GLFWwindow* handle)
        : m_WindowHandle(handle)
    {
        PD_CORE_ASSERT(handle, "Window handle is null!");
    }

    void OpenGLGraphicsContext::Init()
    {
        glfwMakeContextCurrent(m_WindowHandle);
        int status = glewInit();
        PD_CORE_ASSERT(status == GLEW_OK, "Failed to initialize GLEW!");

        const char* version_str = (const char*)glGetString(GL_VERSION);
        const char* vendor_str = (const char*)glGetString(GL_VENDOR);
        const char* renderer_str = (const char*)glGetString(GL_RENDERER);
        PD_CORE_TRACE("Version: {}", version_str);
        PD_CORE_TRACE("Vendor: {}", vendor_str);
        PD_CORE_TRACE("Renderer: {}", renderer_str);

        glEnable(GL_DEBUG_OUTPUT);
        // glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
        // glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, nullptr, GL_FALSE);
        glDebugMessageCallback(message_callback, nullptr);

        glEnable(GL_DEPTH_TEST);
        glEnable(GL_MULTISAMPLE); 

        glEnable(GL_CULL_FACE);  
        glCullFace(GL_BACK);  
        glFrontFace(GL_CCW); 
    }   

    void OpenGLGraphicsContext::SwapBuffers()
    {
        glfwSwapBuffers(m_WindowHandle);
    }
}