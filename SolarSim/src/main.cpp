#include <iostream>

#include <Pandora.hpp>

class SolarSimApp : public Pandora::Application
{
public:
    void OnEvent(Pandora::Event& e) override
    {
        Pandora::Application::OnEvent(e);

        Pandora::EventDispatcher dispatcher(e);
        dispatcher.Dispatch<Pandora::MouseMovedEvent>(PD_BIND_EVENT_FN(SolarSimApp::OnMouseMoveEvent));
    }

    bool OnMouseMoveEvent(Pandora::MouseMovedEvent& e)
    {
        PD_INFO("{}", e);

        return false;
    }
};

Pandora::Scope<Pandora::Application> Pandora::CreateApplication()
{
    return Pandora::CreateScope<SolarSimApp>();
}