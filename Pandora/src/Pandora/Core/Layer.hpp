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

        virtual void OnAttach() = 0;
        virtual void OnDetach() = 0;
        virtual void OnUpdate(Timestep ts) = 0;
        virtual void OnRender() = 0;
        virtual void OnEvent(Event& event) = 0;
    };
}