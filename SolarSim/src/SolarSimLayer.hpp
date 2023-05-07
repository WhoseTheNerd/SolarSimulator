#pragma once

#include <Pandora.hpp>

#include "Planet.hpp"

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
    private:
        std::vector<Pandora::Ref<Planet>> m_Planets;

        Pandora::PerspectiveCameraController m_CameraController;

        bool m_MouseCaptured = true;
    };

}