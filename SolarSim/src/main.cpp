#include <iostream>

#include <Pandora.hpp>

class SolarSimLayer : public Pandora::Layer
{
public:
    virtual void OnAttach() override {}
    virtual void OnDetach() override {}
    virtual void OnUpdate(Pandora::Timestep ts) override {}
    virtual void OnRender() override {}
    virtual void OnEvent(Pandora::Event& event) override 
    {
        Pandora::EventDispatcher dispatcher(event);
        dispatcher.Dispatch<Pandora::MouseMovedEvent>(PD_BIND_EVENT_FN(SolarSimLayer::OnMouseMoveEvent));
    }

private:
    bool OnMouseMoveEvent(Pandora::MouseMovedEvent& e)
    {
        PD_INFO("{}", e);

        return false;
    }
};

class SolarSimApp : public Pandora::Application
{
public:
    SolarSimApp()
    {
        PushLayer(new SolarSimLayer());
    }
};

Pandora::Scope<Pandora::Application> Pandora::CreateApplication()
{
    return Pandora::CreateScope<SolarSimApp>();
}