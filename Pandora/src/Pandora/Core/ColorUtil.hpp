#pragma once

#include "Pandora/Core/Base.hpp"

#include <glm/glm.hpp>

namespace Pandora {

    constexpr glm::vec3 FromRGB(uint8_t red, uint8_t green, uint8_t blue)
    {
        return {red / 255.0f, green / 255.0f, blue / 255.0f};
    }

    inline glm::vec3 FromHex(const char* hex)
    {
        uint8_t red, green, blue;
        sscanf(hex, "#%02x%02x%02x", &red, &green, &blue);
        return FromRGB(red, green, blue);
    }
}