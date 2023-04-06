#include <iostream>

#include <Pandora.hpp>
#include <Pandora/Core/EntryPoint.hpp>

#include "SolarSimLayer.hpp"

class SolarSimApp : public Pandora::Application
{
public:
    SolarSimApp()
    {
        PushLayer(new SolarSim::SolarSimLayer());
    }
};

Pandora::Scope<Pandora::Application> Pandora::CreateApplication()
{
    return Pandora::CreateScope<SolarSimApp>();
}