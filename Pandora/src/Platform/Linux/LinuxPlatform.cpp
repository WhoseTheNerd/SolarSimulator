#include "Pandora/Core/Platform.hpp"

#include <GLFW/glfw3.h>

namespace Pandora {

    float Platform::GetTime()
    {
        return static_cast<float>(glfwGetTime());
    }
}