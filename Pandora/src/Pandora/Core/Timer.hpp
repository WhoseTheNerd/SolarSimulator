#pragma once

#include "Pandora/Core/Base.hpp"

#include <chrono>

namespace Pandora {

    class Timer
    {
    public:
        Timer(const std::string& name)
            : m_Name(name), m_Start(std::chrono::high_resolution_clock::now())
        {
        }

        ~Timer()
        {
            auto end = std::chrono::high_resolution_clock::now();
            auto duration = std::chrono::duration_cast<std::chrono::seconds>(end - m_Start).count();
            PD_CORE_INFO("{} took {} s", m_Name, duration);
        }
    private:
        std::string m_Name;
        std::chrono::high_resolution_clock::time_point m_Start;
    };
}