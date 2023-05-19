#pragma once

#include <Pandora.hpp>

#include "Planet.hpp"
#include "OrbitingCamera.hpp"

namespace SolarSim {

    class SolarSimLayer : public Pandora::Layer
    {
    public:
        SolarSimLayer();
        virtual ~SolarSimLayer();

        virtual void OnAttach() override;
        virtual void OnDetach() override;
        virtual void OnUpdate(Pandora::Timestep ts) override;
        virtual void OnRender() override;
        virtual void OnEvent(Pandora::Event& event) override;
        virtual void OnImGuiRender() override;
    private:
        bool OnKeyPressed(Pandora::KeyPressedEvent& e);
        bool OnWindowResize(Pandora::WindowResizeEvent& e);
    private:
        std::vector<Pandora::Ref<Planet>> m_Planets;

        //Pandora::PerspectiveCameraController m_CameraController;
        OrbitingCamera m_OrbitingCamera;

        bool m_MouseCaptured = true;
        bool m_StartSimulation = false;
        const char** followPlanetItems;
        const char* followPlanetName;
    };

}