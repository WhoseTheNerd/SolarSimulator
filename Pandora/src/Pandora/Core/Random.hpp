#pragma once

#include "Pandora/Core/Base.hpp"

#include <random>
#include <glm/glm.hpp>

namespace Pandora {

    class Random
    {
    public:
        static void Init()
        {
            s_RandomEngine.seed(std::random_device()());
        }

        static uint32_t UInt()
        {
            return s_Distribution(s_RandomEngine);
        }

        static uint32_t UInt(uint32_t min, uint32_t max)
        {
            return min + (s_Distribution(s_RandomEngine) % (max - min + 1));
        }

        static float Float()
        {
            return static_cast<float>(s_Distribution(s_RandomEngine)) / static_cast<float>(std::numeric_limits<uint32_t>::max());
        }

        static double Double()
        {
            return static_cast<double>(s_Distribution(s_RandomEngine)) / static_cast<double>(std::numeric_limits<uint32_t>::max());
        }

        static glm::vec2 Vec2()
        {
            return glm::vec2{Float(), Float()};
        }

        static glm::vec2 Vec2(float min, float max)
        {
            return glm::vec2{Float() * (max - min) + min, Float() * (max - min) + min};
        }

        static glm::vec3 Vec3()
        {
            return glm::vec3{Float(), Float(), Float()};
        }

        static glm::vec3 Vec3(float min, float max)
        {
            return glm::vec3{Float() * (max - min) + min, Float() * (max - min) + min, Float() * (max - min) + min};
        }

        static glm::vec4 Vec4()
        {
            return glm::vec4{Float(), Float(), Float(), Float()};
        }

        static glm::vec4 Vec4(float min, float max)
        {
            return glm::vec4{Float() * (max - min) + min, Float() * (max - min) + min, Float() * (max - min) + min, Float() * (max - min) + min};
        }
    private:
        static inline thread_local std::mt19937 s_RandomEngine;
        static inline std::uniform_int_distribution<std::mt19937::result_type> s_Distribution;
    };
}