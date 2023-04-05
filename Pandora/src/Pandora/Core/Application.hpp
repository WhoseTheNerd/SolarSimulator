#pragma once

#include "Base.hpp"
#include "Window.hpp"

#include "Pandora/Events/Event.hpp"
#include "Pandora/Events/ApplicationEvent.hpp"

namespace Pandora {

    class Application
    {
    public:
        Application();
        virtual ~Application();

        void Run();

        virtual void OnEvent(Event& e);
    private:
        bool OnWindowClose(WindowCloseEvent& e);
    private:
        bool m_Running;
        Scope<Window> m_Window;
    };

    Scope<Application> CreateApplication();
}