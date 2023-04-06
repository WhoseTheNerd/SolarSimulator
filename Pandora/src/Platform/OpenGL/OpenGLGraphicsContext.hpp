#pragma once

#include "Pandora/Graphics/GraphicsContext.hpp"

struct GLFWwindow;

namespace Pandora {

    class OpenGLGraphicsContext : public GraphicsContext
    {
    public:
        OpenGLGraphicsContext(GLFWwindow* handle);

        virtual void Init() override;
        virtual void SwapBuffers() override;
    private:
        GLFWwindow* m_WindowHandle;
    };
}