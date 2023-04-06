#pragma once

#include "Pandora/Core/Base.hpp"

struct GLFWwindow;

namespace Pandora {

    class GraphicsContext
    {
    public:
        virtual void Init() = 0;
        virtual void SwapBuffers() = 0;

        static Scope<GraphicsContext> Create(GLFWwindow* window_handle);
    };
}