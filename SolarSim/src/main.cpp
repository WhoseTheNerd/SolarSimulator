#include <iostream>

#include <Pandora.hpp>

class SolarSimApp : public Pandora::Application
{
public:
    SolarSimApp()
    {
        PD_INFO("It is working!");
    }
};

Pandora::Scope<Pandora::Application> Pandora::CreateApplication()
{
    return Pandora::CreateScope<SolarSimApp>();
}