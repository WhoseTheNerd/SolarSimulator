#pragma once

#include "Pandora/Core/Base.hpp"
#include "Pandora/Core/Window.hpp"
#include "Pandora/Core/Layer.hpp"
#include "Pandora/Core/LayerStack.hpp"
#include "Pandora/Core/Timestep.hpp"

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

        void PushLayer(Layer* layer);
        void PushOverlay(Layer* overlay);

        inline Window& GetWindow() { return *m_Window; }    

        inline static Application& Get() { return *s_Instance; }
    private:
        bool OnWindowClose(WindowCloseEvent& e);
    private:
        bool m_Running;
        Scope<Window> m_Window;
        LayerStack m_LayerStack;
        float m_LastFrameTime = 0.0f;
    private:
        static Application* s_Instance;
    };

    Scope<Application> CreateApplication();
}