#pragma once

#include "Pandora/Core/Log.hpp"
#include "Pandora/Core/Application.hpp"

extern Pandora::Scope<Pandora::Application> Pandora::CreateApplication();

int main(int argc, char** argv)
{
    Pandora::Log::Init();
    Pandora::Scope<Pandora::Application> app = Pandora::CreateApplication();
    app->Run();
}