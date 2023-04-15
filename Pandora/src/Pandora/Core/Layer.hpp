#pragma once

#include "Pandora/Core/Base.hpp"
#include "Pandora/Core/Timestep.hpp"
#include "Pandora/Events/Event.hpp"

namespace Pandora {

    class Layer
    {
    public:
        Layer() = default;
        virtual ~Layer() = default;

        virtual void OnAttach() {};
        virtual void OnDetach() {};
        virtual void OnUpdate(Timestep ts) {};
        virtual void OnRender() {};
        virtual void OnImGuiRender() {};
        virtual void OnEvent(Event& event) {};
    };
}